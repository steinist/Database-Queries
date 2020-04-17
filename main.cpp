#include <iostream>
#include <string>

#include "table.h"

using namespace std;

const char space = ' ';

void
_print_dimensions(const Table *table)
{
	cout << "numAttrs: " << table->getNumAttrs() << " numEntries: " << table->getNumEntries() << endl;
}

void
_test_table01()
{
	cout << "Test Table 01" << endl;

	Table *a = new Table;

	_print_dimensions(a);

	// Add attribute at index 0
	// Valid indices: -1, 0
	cout << boolalpha << a->addAttribute("A", 0) << endl;

	_print_dimensions(a);

	// Add attribute at index 1, adds attributes at the end
	// Valid indices: -1, 0, 1
	cout << boolalpha << a->addAttribute("B", 1) << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << endl << a->getAttribute(1) << endl;

	delete a;

	cout << endl;
}

void
_test_table02()
{
	cout << "Test Table 02" << endl;

	Table *a = new Table;

	// Use default index -1 to always add attributes at the end
	cout << boolalpha << a->addAttribute("A") << space;
	cout << boolalpha << a->addAttribute("B") << space;
	cout << boolalpha << a->addAttribute("C") << space;
	cout << boolalpha << a->addAttribute("D") << space;
	cout << boolalpha << a->addAttribute("E") << endl;

	_print_dimensions(a);

	// Add attribute
	// Valid indices: -1, 0, 1, 2, 3, 4, 5
	cout << boolalpha << a->addAttribute("FAIL", -2) << space;
	cout << boolalpha << a->addAttribute("FAIL", 6) << space;
	cout << boolalpha << a->addAttribute("F", 2) << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << space << a->getAttribute(1) << space << a->getAttribute(2) << space;
	cout << a->getAttribute(3) << space << a->getAttribute(4) << space << a->getAttribute(5) << endl;

	// Delete attribute
	// Valid indices: 0, 1, 2, 3, 4, 5
	cout << boolalpha << a->deleteAttribute(-1) << space;
	cout << boolalpha << a->deleteAttribute(6) << space;
	cout << boolalpha << a->deleteAttribute(2) << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << space << a->getAttribute(1) << space << a->getAttribute(2) << space;
	cout << a->getAttribute(3) << space << a->getAttribute(4) << endl;

	// Delete all attributes
	cout << boolalpha << a->deleteAttribute(4) << space;
	cout << boolalpha << a->deleteAttribute(3) << space;
	cout << boolalpha << a->deleteAttribute(2) << space;
	cout << boolalpha << a->deleteAttribute(1) << space;
	cout << boolalpha << a->deleteAttribute(0) << endl;

	_print_dimensions(a);

	// At this point, a->attrs should be nullptr

	delete a;

	cout << endl;
}

void
_test_table03()
{
	cout << "Test Table 03" << endl;

	Table *a = new Table;

	a->addAttribute("A");
	a->addAttribute("B");
	a->addAttribute("C");

	string entry1[] = {"A1", "B1", "C1"};
	string entry2[] = {"A2", "B2", "C2"};

	_print_dimensions(a);

	// Add entry at index 0
	// Valid indices: -1, 0
	cout << boolalpha << a->addEntry(entry1, 0) << endl;

	_print_dimensions(a);

	// Add entry at index 1
	// Valid indices: -1, 0, 1
	cout << boolalpha << a->addEntry(entry2, 1) << endl;

	_print_dimensions(a);

	// Get values of entries
	cout << a->getEntry(0, 0) << space << a->getEntry(0, 1) << space << a->getEntry(0, 2) << endl;
	cout << a->getEntry(1, 0) << space << a->getEntry(1, 1) << space << a->getEntry(1, 2) << endl;

	delete a;

	cout << endl;
}

void
_test_table04()
{
	cout << "Test Table 04" << endl;

	Table *a = new Table;

	a->addAttribute("A");
	a->addAttribute("B");
	a->addAttribute("C");

	string entry1[] = {"A1", "B1", "C1"};
	string entry2[] = {"A2", "B2", "C2"};
	string entry3[] = {"A3", "B3", "C3"};
	string entry4[] = {"A4", "B4", "C4"};
	string entry5[] = {"A5", "B5", "C5"};

	a->addEntry(entry1);
	a->addEntry(entry2);
	a->addEntry(entry3);
	a->addEntry(entry4);

	_print_dimensions(a);

	// Add entry
	// Valid indices: -1, 0, 1, 2, 3, 4
	cout << boolalpha << a->addEntry(entry5, -2) << space;
	cout << boolalpha << a->addEntry(entry5, 5) << space;
	cout << boolalpha << a->addEntry(entry5, 2) << endl;

	_print_dimensions(a);

	cout << a->getEntry(0, 0) << space << a->getEntry(0, 1) << space << a->getEntry(0, 2) << endl;
	cout << a->getEntry(1, 0) << space << a->getEntry(1, 1) << space << a->getEntry(1, 2) << endl;
	cout << a->getEntry(2, 0) << space << a->getEntry(2, 1) << space << a->getEntry(2, 2) << endl;
	cout << a->getEntry(3, 0) << space << a->getEntry(3, 1) << space << a->getEntry(3, 2) << endl;
	cout << a->getEntry(4, 0) << space << a->getEntry(4, 1) << space << a->getEntry(4, 2) << endl;

	// Delete entry
	// Valid indices: 0, 1, 2, 3, 4, 5
	cout << boolalpha << a->deleteEntry(-1) << space;
	cout << boolalpha << a->deleteEntry(6) << space;
	cout << boolalpha << a->deleteEntry(2) << endl;

	_print_dimensions(a);

	cout << a->getEntry(0, 0) << space << a->getEntry(0, 1) << space << a->getEntry(0, 2) << endl;
	cout << a->getEntry(1, 0) << space << a->getEntry(1, 1) << space << a->getEntry(1, 2) << endl;
	cout << a->getEntry(2, 0) << space << a->getEntry(2, 1) << space << a->getEntry(2, 2) << endl;
	cout << a->getEntry(3, 0) << space << a->getEntry(3, 1) << space << a->getEntry(3, 2) << endl;

	delete a;

	cout << endl;
}

void
_test_table05()
{
	cout << "Test Table 05" << endl;

	Table *a = new Table;

	a->addAttribute("A");

	string entry1[] = {"A1"};
	string entry2[] = {"A2"};
	string entry3[] = {"A3"};
	string entry4[] = {"A4"};

	a->addEntry(entry1);
	a->addEntry(entry2);
	a->addEntry(entry3);
	a->addEntry(entry4);

	_print_dimensions(a);

	// Add attribute at the end with empty string as default value
	cout << a->addAttribute("B") << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << space << a->getAttribute(1) << endl;

	cout << a->getEntry(0, 0) << space << a->getEntry(0, 1) << endl;
	cout << a->getEntry(1, 0) << space << a->getEntry(1, 1) << endl;
	cout << a->getEntry(2, 0) << space << a->getEntry(2, 1) << endl;
	cout << a->getEntry(3, 0) << space << a->getEntry(3, 1) << endl;

	// Add attribute at the end with default value "DEFAULT"
	cout << a->addAttribute("C", -1, "DEFAULT") << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << space << a->getAttribute(1) << space << a->getAttribute(2) << endl;

	cout << a->getEntry(0, 0) << space << a->getEntry(0, 1) << space << a->getEntry(0, 2) << endl;
	cout << a->getEntry(1, 0) << space << a->getEntry(1, 1) << space << a->getEntry(1, 2) << endl;
	cout << a->getEntry(2, 0) << space << a->getEntry(2, 1) << space << a->getEntry(2, 2) << endl;
	cout << a->getEntry(3, 0) << space << a->getEntry(3, 1) << space << a->getEntry(3, 2) << endl;


	delete a;

	cout << endl;
}

void
_test_table06()
{
	cout << "Test Table 06" << endl;

	Table *a = new Table;

	a->addAttribute("A");
	a->addAttribute("B");
	a->addAttribute("C");

	string entry1[] = {"A1", "B1", "C1"};
	string entry2[] = {"A2", "B2", "C2"};
	string entry3[] = {"A3", "B3", "C3"};
	string entry4[] = {"A4", "B4", "C4"};

	a->addEntry(entry1);
	a->addEntry(entry2);
	a->addEntry(entry3);
	a->addEntry(entry4);

	_print_dimensions(a);

	// Delete entry
	// Valid indices: 0, 1, 2, 3, 4
	cout << boolalpha << a->deleteEntry(-1) << space;
	cout << boolalpha << a->deleteEntry(5) << space;
	cout << boolalpha << a->deleteEntry(2) << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << space << a->getAttribute(1) << space << a->getAttribute(2) << endl;

	cout << a->getEntry(0, 0) << space << a->getEntry(0, 1) << space << a->getEntry(0, 2) << endl;
	cout << a->getEntry(1, 0) << space << a->getEntry(1, 1) << space << a->getEntry(1, 2) << endl;
	cout << a->getEntry(2, 0) << space << a->getEntry(2, 1) << space << a->getEntry(2, 2) << endl;

	// Delete all entries
	cout << a->deleteEntry(2) << space;
	cout << a->deleteEntry(1) << space;
	cout << a->deleteEntry(0) << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << space << a->getAttribute(1) << space << a->getAttribute(2) << endl;

	// At this point, a->entries should be nullptr

	delete a;

	cout << endl;
}

void
_test_table07()
{
	cout << "Test Table 07" << endl;

	Table *a = new Table;

	a->addAttribute("A");
	a->addAttribute("B");
	a->addAttribute("C");

	string entry1[] = {"A1", "B1", "C1"};
	string entry2[] = {"A2", "B2", "C2"};
	string entry3[] = {"A3", "B3", "C3"};
	string entry4[] = {"A4", "B4", "C4"};

	a->addEntry(entry1);
	a->addEntry(entry2);
	a->addEntry(entry3);
	a->addEntry(entry4);

	_print_dimensions(a);

	// Delete attribute
	cout << boolalpha << a->deleteAttribute(2) << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << space << a->getAttribute(1) << endl;

	cout << a->getEntry(0, 0) << space << a->getEntry(0, 1) << endl;
	cout << a->getEntry(1, 0) << space << a->getEntry(1, 1) << endl;
	cout << a->getEntry(2, 0) << space << a->getEntry(2, 1) << endl;

	cout << boolalpha << a->deleteAttribute(1) << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << endl;

	cout << a->getEntry(0, 0) << endl;
	cout << a->getEntry(1, 0) << endl;
	cout << a->getEntry(2, 0) << endl;

	cout << boolalpha << a->deleteAttribute(0) << endl;

	_print_dimensions(a);

	// At this point, a->attrs and a->entries should be nullptr

	delete a;

	cout << endl;
}

void
_test_table08()
{
	cout << "Test Table 08" << endl;

	Table *a = new Table;
	Table *b = new Table;
	Table *c = new Table;
	Table *d = new Table;

	a->addAttribute("A");
	a->addAttribute("B");
	a->addAttribute("C");

	b->addAttribute("A");
	b->addAttribute("B");
	b->addAttribute("C");
	b->addAttribute("D");

	// Different attributes. Cannot append
	cout << boolalpha << a->append(*b) << endl;

	c->addAttribute("B");
	c->addAttribute("A");
	c->addAttribute("C");

	// Attributes in different order. Cannot append
	cout << boolalpha << a->append(*c) << endl;

	d->addAttribute("A");
	d->addAttribute("B");
	d->addAttribute("C");

	// Attributes are the same with same order. Append should return true
	cout << boolalpha << a->append(*d) << endl;

	_print_dimensions(a);

	string entry1[] = {"A1", "B1", "C1"};
	string entry2[] = {"A2", "B2", "C2"};

	a->addEntry(entry1);
	d->addEntry(entry2);

	_print_dimensions(a);

	cout << boolalpha << a->append(*d) << endl;

	_print_dimensions(a);

	cout << a->getAttribute(0) << space << a->getAttribute(1) << space << a->getAttribute(2) << endl;

	cout << a->getEntry(0, 0) << space << a->getEntry(0, 1) << space << a->getEntry(0, 2) << endl;
	cout << a->getEntry(1, 0) << space << a->getEntry(1, 1) << space << a->getEntry(1, 2) << endl;

	_print_dimensions(d);

	cout << d->getAttribute(0) << space << d->getAttribute(1) << space << d->getAttribute(2) << endl;

	cout << d->getEntry(0, 0) << space << d->getEntry(0, 1) << space << d->getEntry(0, 2) << endl;

	delete a;
	delete b;
	delete c;
	delete d;

	cout << endl;
}


int
main()
{
	_test_table01();

	_test_table02();

	_test_table03();

	_test_table04();

	_test_table05();

	_test_table06();

	_test_table07();

	_test_table08();

	return 0;
}
