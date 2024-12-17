package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Missing a file name argument")
		os.Exit(1)
	}

	fileName := os.Args[1]

	file, err := os.Open(fileName)

	if err != nil {
		fmt.Fprintf(os.Stderr, "Error opening file")
		os.Exit(1)
	}

	defer file.Close()

	var leftList []int
	var rightMap = make(map[int]int)

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		numbers := strings.Fields(scanner.Text())
		if len(numbers) != 2 {
			continue
		}

		if left, err := strconv.Atoi(numbers[0]); err == nil {
			leftList = append(leftList, left)
		}

		if right, err := strconv.Atoi(numbers[1]); err == nil {
			rightMap[right]++
		}
	}

	result := 0

	for _, left := range leftList {
		count := rightMap[left]
		result += (left * count)
	}
	fmt.Printf("%d", result)

	return
}
