#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct File {
    int id;
    int size;
    int start_index;  // Where the file starts in the expanded representation
};

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Missing input text file";
        return 0;
    }
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "There was an error opening file";
        return 1;
    }
    
    string line;
    vector<string> diskmap;
    vector<File> files;
    int current_index = 0;
    
    while (getline(file, line)) {
        bool isFile = true;
        for (int i = 0; i < line.length(); i++) {
            int length = line[i] - '0';
            if (isFile) {
                // Store file information
                File f = {
                    .id = (int)files.size(),
                    .size = length,
                    .start_index = current_index
                };
                files.push_back(f);
                
                // Add file blocks to diskmap
                for (int j = 0; j < length; j++) {
                    diskmap.push_back(to_string(files.size() - 1));
                }
                current_index += length;
                isFile = false;
            } else {
                // Add free space
                for (int j = 0; j < length; j++) {
                    diskmap.push_back(".");
                }
                current_index += length;
                isFile = true;
            }
        }
    }

    // Sort files by ID in descending order
    sort(files.begin(), files.end(), 
         [](const File& a, const File& b) { return a.id > b.id; });

    // Process each file from highest ID to lowest
    for (const File& f : files) {
        // Find leftmost space that can fit this file
        int space_pos = -1;
        for (int i = 0; i < diskmap.size(); i++) {
            if (diskmap[i] == ".") {
                // Count consecutive free spaces
                int space_size = 0;
                int j = i;
                while (j < diskmap.size() && diskmap[j] == "." && space_size < f.size) {
                    space_size++;
                    j++;
                }
                if (space_size >= f.size) {
                    space_pos = i;
                    break;
                }
                i = j - 1;  // Skip to end of this space block
            }
        }

        // If we found a suitable space and it's to the left of the file
        if (space_pos != -1 && space_pos < f.start_index) {
            // Move the entire file
            string file_id = to_string(f.id);
            // Clear old location
            for (int i = f.start_index; i < f.start_index + f.size; i++) {
                if (i < diskmap.size() && diskmap[i] == file_id) {
                    diskmap[i] = ".";
                }
            }
            // Place in new location
            for (int i = 0; i < f.size; i++) {
                diskmap[space_pos + i] = file_id;
            }
        }
    }

    // Calculate checksum
    long long sum = 0;
    for (int i = 0; i < diskmap.size(); ++i) {
        if (diskmap[i] != ".") {
            sum += (stoll(diskmap[i]) * i);
        }
    }
    cout << sum << endl;
    return 0;
}