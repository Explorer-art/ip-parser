package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"time"
	"strings"
)

func main() {
	if len(os.Args) < 3 {
		fmt.Printf("Example: %s <input_file> <output_file>\n", os.Args[0])
		return
	}

	input_filename := os.Args[1]
	output_filename := os.Args[2]

	start := time.Now();

	file, err := os.Open(input_filename)

	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	buf := make([]byte, 0, 64*1024)
	scanner.Buffer(buf, 1024*1024)

	for scanner.Scan() {
		string_splited := strings.Split(scanner.Text(), " ")

		if len(string_splited) > 3 {
			f, err2 := os.OpenFile(output_filename, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0744)

			if err2 != nil {
				log.Fatal(err2)
			}

			if _, err2 = f.WriteString(string_splited[3] + "\n"); err2 != nil {
				log.Fatal(err2)
			}

			f.Close()
		}
    }

    if err := scanner.Err(); err != nil {
        log.Fatal(err)
    }

    duration := time.Since(start);

    fmt.Printf("Done! (%.2fs)\n", duration.Seconds())
}