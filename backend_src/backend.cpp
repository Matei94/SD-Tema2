#include <iostream>
#include "backend.h"


Backend::Backend()
{
	// TODO: Initialization magic
}

Backend::~Backend()
{
	// TODO: Destruction magic
}

void Backend::Cut(const int start, const int stop)
{
	// TODO: Actual text cutting
	std::cout << "Cut from " << start << " to " << stop << "\n";
}

void Backend::Copy(const int start, const int stop)
{
	// TODO: Actual text copying
	std::cout << "Copy from " << start << " to " << stop << "\n";
}

void Backend::Paste(const int start)
{
	// TODO: Actual text... well, you get the idea
	std::cout << "Paste from " << start << "\n";
}

void Backend::Undo(void)
{
	// TODO:
	std::cout << "Undo!\n";
}

void Backend::Redo(void)
{
	// TODO:
	std::cout << "Redo!\n";
}

void Backend::Add(const int index, const char *word)
{
	// TODO: add the word to the text
	// pay some attention to invalid pointers!
	std::cout << "Adding \"" << word << "\" from " << index << "\n";
}

const char *Backend::GetText(void)
{
	// TODO: return the full stored text
	// This will be called *a lot*
	std::cout << "Sending back text!\n";

	return "";
}

