package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

// Check if a sequence is valid (all increasing or all decreasing with valid differences)
func isValidSequence(vals []int) bool {
	if len(vals) < 2 {
		return true
	}

	isIncreasing := true
	isDecreasing := true

	for i := 0; i < len(vals)-1; i++ {
		diff := math.Abs(float64(vals[i] - vals[i+1]))
		if diff < 1 || diff > 3 {
			return false
		}
		if vals[i] >= vals[i+1] {
			isIncreasing = false
		}
		if vals[i] <= vals[i+1] {
			isDecreasing = false
		}
	}

	return isIncreasing || isDecreasing
}

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

	scanner := bufio.NewScanner(file)
	numSafe := 0

	for scanner.Scan() {
		level := strings.Fields(scanner.Text())
		vals := make([]int, len(level))
		for i, v := range level {
			val, err := strconv.Atoi(v)
			if err != nil {
				fmt.Fprintf(os.Stderr, "Error converting string to int")
				os.Exit(1)
			}
			vals[i] = val
		}

		// First check if sequence is already safe
		if isValidSequence(vals) {
			numSafe++
			continue
		}

		// Try removing each number one at a time
		isSafe := false
		for i := 0; i < len(vals); i++ {
			// Create new slice without current element
			newVals := make([]int, 0, len(vals)-1)
			newVals = append(newVals, vals[:i]...)
			newVals = append(newVals, vals[i+1:]...)

			if isValidSequence(newVals) {
				isSafe = true
				break
			}
		}

		if isSafe {
			numSafe++
		}
	}

	fmt.Printf("%d", numSafe)
}
