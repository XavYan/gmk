#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <getopt.h>

// Modos
std::string header = "include";
std::string source = "src";
std::string build = "build";

std::string headerExt = "hpp";
std::string sourceExt = "cpp";

std::string nameOfFile = "main";

void help () {
	std::cout << "Usage: ./gmk [options] [-o class]...\n";
	std::cout << "Options:\n";
	std::cout << "-h --help\t\tDisplay this information.\n";
	std::cout << "-n --name\t\tSet the name of the executable file. By default: main\n";
	std::cout << "-i --header-dir\t\tSet the directory of the headers class. By default: include\n";
	std::cout << "-c --header-ext\t\tSet the extension of the headers class. By default: hpp\n";
	std::cout << "-s --source-dir\t\tSet the directory of the class source. By default: src\n";
	std::cout << "-d --source-ext\t\tSet the extension of the class source. By default: cpp\n";
	std::cout << "-b --build\t\tSet the directory where '.o' files are saved. By default: build\n";
	std::cout << "-o --class\t\tSet the classes the program needs to be compiled with. Without it, it only compiles the main file.\n";
	std::cout << "\t\t\tIMPORTANT: YOU NEED TO USE THIS ARGUMENT BEHIND THE OTHER.\n";
}

int main(int argc, char *argv[]) {

	static struct option long_options[] = {
		{"help",	no_argument,	0, 'h'},
		{"name",	required_argument,	0,	'n'},
		{"header-dir",	required_argument,	0,	'i'},
		{"source-dir", 	required_argument,	0,	's'},
		{"header-ext",	required_argument,	0,	'c'},
		{"source-ext",	required_argument,	0,	'd'},
		{"build",		required_argument,	0,	'b'},
		{"class",		no_argument,		0,	'o'},
		{0, 0, 0, 0}
	};

	int c;
	int index = 1;
	while ((c = getopt_long(argc, argv, "hn:i:s:c:d:b:o", long_options, nullptr)) != -1) {
		
		index++;

		if (c == 'o') break;

		switch(c) {
			case 'h':
				help();
				return -1;
			case 'n':
				if (optarg) {
					nameOfFile = optarg;
					index++;
				}
				break;
			case 'i':
				if (optarg) {
					header = optarg;
					index++;
				}
				break;
			case 's':
				if (optarg) {
					source = optarg;
					index++;
				}
				break;
			case 'c':
				if (optarg) {
					headerExt = optarg;
					index++;
				}
				break;
			case 'd':
				if (optarg) {
					sourceExt = optarg;
					index++;
				}
				break;
			case 'b':
				if (optarg) {
					build = optarg;
					index++;
				}
				break;
			default:
				std::cerr << "Error with the arguments. Please use './gmk --help' if you don't know how to use this program.\n";
				return -1;
		}
	}

	std::ofstream make("Makefile");

	make << "CC=g++\n";
	make << "CFLAGS=-g -Wall -Wextra -std=c++17\n";

	std::string all = "all: "+source+"/main."+sourceExt;
	for (int i = index; i < argc; i++) {
		all += " "+build+"/"+std::string(argv[i])+".o";
	}
	all += '\n';
	
	all += std::string("\t$(CC) $(CFLAGS) -o ")+nameOfFile+" "+all.substr(5)+"\n\n";
	
	for (int i = index; i < argc; i++) {
		all += build+"/"+std::string(argv[i])+".o: "+header+"/"+std::string(argv[i])+"."+headerExt+" "+source+"/"+std::string(argv[i])+"."+sourceExt+"\n";
		all += std::string("\t$(CC) $(CFLAGS) -c -o "+build+"/")+std::string(argv[i])+".o "+source+"/"+std::string(argv[i])+"."+sourceExt+"\n\n";
	}

	all += ".PHONY: clean\n\n";
	all += "clean:\n\trm -rf "+build+"/*.o\n";

	make << all;

	make.close();
	return 0;
}
