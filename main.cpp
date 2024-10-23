#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct recordTemplate
{
	unsigned int record;
	fstream db;
	string tmp;
	string name;
	string family;
	string address;
	string email;
	string mobile;
	string home;

	bool case_insensitive_match(string s1, string s2);
	void reset(void);
	void addNewRecord(void);
	void deleteRecord(void);
	void editRecord(void);
	void searchRecords(void);
	void showAll(void);

	void dbout(bool atEnd);
	void dbin(void);
	void dbclose(void);
};

int main()
{
	recordTemplate data;
	int selection;
	while (true)
	{
		system("cls");
		cout << endl;
		cout << " PhoneBook Main Menu" << endl;
		cout << "\t1. Add new record" << endl;
		cout << "\t2. Delete a record" << endl;
		cout << "\t3. Edit and existing record" << endl;
		cout << "\t4. Search the records" << endl;
		cout << "\t5. Show all the records" << endl;
		cout << "\t6. Exit" << endl;
		cout << endl;
		cout << "Select by entering a number from 1 to 6 : ";
		cin >> selection;
		if (selection == 1) {
			data.reset();
			data.addNewRecord();
			continue;
		}
		else if (selection == 2) {
			data.reset();
			data.deleteRecord();
			continue;
		}
		else if (selection == 3) {
			data.reset();
			data.editRecord();
			continue;
		}
		else if (selection == 4) {
			data.reset();
			data.searchRecords();
			continue;
		}
		else if (selection == 5) {
			data.reset();
			data.showAll();
			continue;
		}
		else if (selection == 6) {
			cout << "\nAre you sure you want to exit? ( Yes / No ) : ";
			cin >> data.tmp;
			if (data.case_insensitive_match(data.tmp, "yes")) {
				break;
			}
		}
		else
			continue;
	}
	return 0;
}

bool recordTemplate::case_insensitive_match(string s1, string s2) {
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	return (s1.compare(s2) == 0);
}

void recordTemplate::reset(void) {
	record = 0;
	tmp.clear();
	name.clear();
	family.clear();
	address.clear();
	email.clear();
	mobile.clear();
	home.clear();
}

void recordTemplate::addNewRecord(void) {
	string inputs;
	while (true)
	{
		system("cls");
		cout << " New record" << endl;
		cout << "\tName:\t \"" << name << "\"" << endl;
		cout << "\tFamily:\t \"" << family << "\"" << endl;
		cout << "\tAddress: \"" << address << "\"" << endl;
		cout << "\tEmail:\t \"" << email << "\"" << endl;
		cout << "\tMobile:\t \"" << mobile << "\"" << endl;
		cout << "\tHome:\t \"" << home << "\"" << endl << endl;
		cout << " Options:\tCancel ";
		if ((name.empty() + family.empty() + address.empty() + email.empty() + mobile.empty() + home.empty()) < 6) cout << "\tSave";
		cout << "\n\n";
		cout << "Type the property you want to change or an option: ";
		cin >> inputs;
		cout << endl;
		if (case_insensitive_match(inputs, "name")) {
			cout << "Type a new name: ";
			cin.ignore();
			getline(cin, name, '\n');
			continue;
		}
		else if (case_insensitive_match(inputs, "family")) {
			cout << "Type a new family: ";
			cin.ignore();
			getline(cin, family, '\n');
			continue;
		}
		else if (case_insensitive_match(inputs, "address")) {
			cout << "Type a new address: ";
			cin.ignore();
			getline(cin, address, '\n');
			continue;
		}
		else if (case_insensitive_match(inputs, "email")) {
			cout << "Type a new email: ";
			cin.ignore();
			getline(cin, email, '\n');
			continue;
		}
		else if (case_insensitive_match(inputs, "mobile")) {
			cout << "Type a new mobile: ";
			cin.ignore();
			getline(cin, mobile, '\n');
			continue;
		}
		else if (case_insensitive_match(inputs, "home")) {
			cout << "Type a new home: ";
			cin.ignore();
			getline(cin, home, '\n');
			continue;
		}
		else if (case_insensitive_match(inputs, "cancel")) {
			if ((name.empty() + family.empty() + address.empty() + email.empty() + mobile.empty() + home.empty()) < 6) {
				cout << "Cancel without saving? ( Yes / No ) : ";
				cin >> inputs;
				if (case_insensitive_match(inputs, "yes")) {
					cout << "\n\tNothing saved\n\n";
					system("pause");
					system("cls");
					break;
				}
				else
					continue;
			}
			break;
		}
		else if (case_insensitive_match(inputs, "save")) {
			if ((name.empty() + family.empty() + address.empty() + email.empty() + mobile.empty() + home.empty()) < 6) {
				cout << "Save new record and exit? ( Yes / No ) : ";
				cin >> inputs;
				if (case_insensitive_match(inputs, "yes")) {
					cout << "\n\tProccessing...\n\n";
					dbout(true);
					db << name << endl;
					db << family << endl;
					db << address << endl;
					db << email << endl;
					db << mobile << endl;
					db << home << endl;
					db.close();
					cout << "\tNew record saved\n\n";
					system("pause");
					system("cls");
					break;
				}
				else
					continue;
			}
			break;
		}
		else {
			continue;
		}
	}
}

void recordTemplate::deleteRecord(void)
{
	unsigned int wantedRecord;
	string inputs;
	while (true)
	{
		system("cls");
		cout << "Enter the record you want to delete or 0 to cancel: ";
		cin >> wantedRecord;
		if (wantedRecord == 0) {
			cout << "\nAre you sure you wanna go back? ( Yes / No ) : ";
			cin >> inputs;
			if (case_insensitive_match(inputs, "yes")) {
				cout << endl << "\tNothing deleted\n\n";
				system("pause");
				break;
			}
			else
				continue;
		}
		dbin();
		record = 0;
		while (!db.eof()) {
			getline(db, name);
			if (db.eof())
				break;
			getline(db, family);
			getline(db, address);
			getline(db, email);
			getline(db, mobile);
			getline(db, home);
			record++;
			if (record == wantedRecord)
				break;
		}
		dbclose();

		if (record < wantedRecord) {
			cout << "\n\tRecord not found!\n\n";
			system("pause");
			continue;
		}
		else {
			cout << endl;
			cout << " Record\t" << record << endl;
			cout << "\tName:\t " << name << endl;
			cout << "\tFamily:\t " << family << endl;
			cout << "\tAddress: " << address << endl;
			cout << "\tEmail:\t " << email << endl;
			cout << "\tMobile:\t " << mobile << endl;
			cout << "\tHome:\t " << home << endl;
			cout << endl;
			cout << "Are you sure you want to delete this record? ( Yes / No ) : ";
			cin >> inputs;
			if (case_insensitive_match(inputs, "yes")) {

				ofstream temporarydb;
				cout << "\n\tProcessing...\n\n";
				dbin();
				temporarydb.open("tdb.db", ios::out | ios::trunc);
				while (!db.eof()) {
					getline(db, name);
					if (db.eof())
						break;
					getline(db, family);
					getline(db, address);
					getline(db, email);
					getline(db, mobile);
					getline(db, home);
					record--;
					if (record == 0)
						continue;
					temporarydb << name << endl;
					temporarydb << family << endl;
					temporarydb << address << endl;
					temporarydb << email << endl;
					temporarydb << mobile << endl;
					temporarydb << home << endl;
				}
				dbclose();
				temporarydb.close();
				remove("database.db");
				rename("tdb.db", "database.db");
				cout << "\tRecord deleted\n\n";
				system("pause");

				break;
			}
			else
				continue;
		}
	}
}

void recordTemplate::editRecord(void)
{
	unsigned int wantedRecord;
	string inputs;
	while (true)
	{
		system("cls");
		cout << "Enter the record you want to edit or 0 to cancel: ";
		cin >> wantedRecord;
		if (wantedRecord == 0) {
			cout << "\nAre you sure you wanna go back? ( Yes / No ) : ";
			cin >> inputs;
			if (case_insensitive_match(inputs, "yes")) {
				cout << endl << "\tNothing edited\n\n";
				system("pause");
				break;
			}
			else
				continue;
		}
		dbin();
		record = 0;
		while (!db.eof()) {
			getline(db, name);
			if (db.eof())
				break;
			getline(db, family);
			getline(db, address);
			getline(db, email);
			getline(db, mobile);
			getline(db, home);
			record++;
			if (record == wantedRecord)
				break;
		}
		dbclose();

		if (record < wantedRecord) {
			cout << "\n\tRecord not found!\n\n";
			system("pause");
			continue;
		}
		else {
			cout << endl;
			cout << " Record\t" << record << endl;
			cout << "\tName:\t " << name << endl;
			cout << "\tFamily:\t " << family << endl;
			cout << "\tAddress: " << address << endl;
			cout << "\tEmail:\t " << email << endl;
			cout << "\tMobile:\t " << mobile << endl;
			cout << "\tHome:\t " << home << endl;
			cout << endl;
			cout << "Are you sure you want to edit this record? ( Yes / No ) : ";
			cin >> inputs;
			if (case_insensitive_match(inputs, "yes")) {
				string inputs;
				while (true)
				{
					system("cls");
					cout << " Record " << record << endl;
					cout << "\tName:\t \"" << name << "\"" << endl;
					cout << "\tFamily:\t \"" << family << "\"" << endl;
					cout << "\tAddress: \"" << address << "\"" << endl;
					cout << "\tEmail:\t \"" << email << "\"" << endl;
					cout << "\tMobile:\t \"" << mobile << "\"" << endl;
					cout << "\tHome:\t \"" << home << "\"" << endl << endl;
					cout << " Options:\tCancel\tSave\n\n";
					cout << "Type the property you want to change or an option: ";
					cin >> inputs;
					cout << endl;
					if (case_insensitive_match(inputs, "name")) {
						cout << "Type a new name: ";
						cin.ignore();
						getline(cin, name, '\n');
						continue;
					}
					else if (case_insensitive_match(inputs, "family")) {
						cout << "Type a new family: ";
						cin.ignore();
						getline(cin, family, '\n');
						continue;
					}
					else if (case_insensitive_match(inputs, "address")) {
						cout << "Type a new address: ";
						cin.ignore();
						getline(cin, address, '\n');
						continue;
					}
					else if (case_insensitive_match(inputs, "email")) {
						cout << "Type a new email: ";
						cin.ignore();
						getline(cin, email, '\n');
						continue;
					}
					else if (case_insensitive_match(inputs, "mobile")) {
						cout << "Type a new mobile: ";
						cin.ignore();
						getline(cin, mobile, '\n');
						continue;
					}
					else if (case_insensitive_match(inputs, "home")) {
						cout << "Type a new home: ";
						cin.ignore();
						getline(cin, home, '\n');
						continue;
					}
					else if (case_insensitive_match(inputs, "cancel")) {
						cout << "Cancel without saving? ( Yes / No ) : ";
						cin >> inputs;
						if (case_insensitive_match(inputs, "yes")) {
							cout << "\n\tNothing saved\n\n";
							system("pause");
							system("cls");
							return;
						}
						else
							continue;
						continue;
					}
					else if (case_insensitive_match(inputs, "save")) {
						cout << "Save record and exit? ( Yes / No ) : ";
						cin >> inputs;
						if (case_insensitive_match(inputs, "yes")) {
							break;
						}
						else
							continue;
						continue;
					}
					else {
						continue;
					}
				}
				ofstream temporarydb;
				recordTemplate temporaryTemplate;
				cout << "\n\tProcessing...\n\n";
				dbin();
				temporarydb.open("tdb.db", ios::out | ios::trunc);
				while (!db.eof()) {
					getline(db, temporaryTemplate.name);
					if (db.eof())
						break;
					getline(db, temporaryTemplate.family);
					getline(db, temporaryTemplate.address);
					getline(db, temporaryTemplate.email);
					getline(db, temporaryTemplate.mobile);
					getline(db, temporaryTemplate.home);
					record--;
					if (record == 0) {
						temporarydb << name << endl;
						temporarydb << family << endl;
						temporarydb << address << endl;
						temporarydb << email << endl;
						temporarydb << mobile << endl;
						temporarydb << home << endl;
						continue;
					}
					temporarydb << temporaryTemplate.name << endl;
					temporarydb << temporaryTemplate.family << endl;
					temporarydb << temporaryTemplate.address << endl;
					temporarydb << temporaryTemplate.email << endl;
					temporarydb << temporaryTemplate.mobile << endl;
					temporarydb << temporaryTemplate.home << endl;
				}
				dbclose();
				temporarydb.close();
				remove("database.db");
				rename("tdb.db", "database.db");
				cout << "\tRecord edited\n\n";
				system("pause");

				break;
			}
			else
				continue;
		}
	}
}

void recordTemplate::searchRecords(void)
{
	string inputs, localTemp;
	int searchIndex = 0;
	while (true)
	{
		system("cls");
		cout << " Search:" << endl;
		cout << "\tName\tFamily\tAddress" << endl;
		cout << "\tEmail\tPhone number" << endl;
		cout << " Options:\tCancel\n\n";
		cout << "Type the property you want to search based on it or an option: ";
		cin >> tmp;
		cout << endl;
		if (case_insensitive_match(tmp, "name")) {
			cout << "Type a name to search: ";
			cin.ignore();
			getline(cin, inputs, '\n');
			tmp = "Name";
			searchIndex = 1;
		}
		else if (case_insensitive_match(tmp, "family")) {
			cout << "Type a family ro search: ";
			cin.ignore();
			getline(cin, inputs, '\n');
			tmp = "Family";
			searchIndex = 2;
		}
		else if (case_insensitive_match(tmp, "address")) {
			cout << "Type an address to search: ";
			cin.ignore();
			getline(cin, inputs, '\n');
			tmp = "Address";
			searchIndex = 3;
		}
		else if (case_insensitive_match(tmp, "email")) {
			cout << "Type an email to search: ";
			cin.ignore();
			getline(cin, inputs, '\n');
			tmp = "Email";
			searchIndex = 4;
		}
		else if (case_insensitive_match(tmp, "phone number") || case_insensitive_match(tmp, "phone") || case_insensitive_match(tmp, "number")) {
			cout << "Type a phone number to search: ";
			cin.ignore();
			getline(cin, inputs, '\n');
			tmp = "Phone nmber";
			searchIndex = 5;
		}
		else if (case_insensitive_match(tmp, "cancel")) {
			cout << "\nAre you sure you wanna go back? ( Yes / No ) : ";
			cin >> tmp;
			if (case_insensitive_match(tmp, "yes")) {
				return;
			}
			else
				continue;
		}
		else
			continue;
		cout << "\nAre you sure you want to search for " << tmp << ": \"" << inputs << "\"? ( Yes / No ) : ";
		cin >> localTemp;
		if (case_insensitive_match(localTemp, "yes"))
			break;
	}
	system("cls");
	cout << " Searching for " << tmp << ": \"" << inputs << "\"\n\n";
	record = 0;
	tmp = "nope";
	dbin();
	while (!db.eof()) {
		getline(db, name);
		if (db.eof())
			break;
		getline(db, family);
		getline(db, address);
		getline(db, email);
		getline(db, mobile);
		getline(db, home);
		record++;
		if (searchIndex == 1) {
			if (case_insensitive_match(name, inputs)) {
				cout << " Record\t" << record << endl;
				cout << "\tName:\t " << name << endl;
				cout << "\tFamily:\t " << family << endl;
				cout << "\tAddress: " << address << endl;
				cout << "\tEmail:\t " << email << endl;
				cout << "\tMobile:\t " << mobile << endl;
				cout << "\tHome:\t " << home << endl;
				tmp = "yep";
			}
		}
		else if (searchIndex == 2) {
			if (case_insensitive_match(family, inputs)) {
				cout << " Record\t" << record << endl;
				cout << "\tName:\t " << name << endl;
				cout << "\tFamily:\t " << family << endl;
				cout << "\tAddress: " << address << endl;
				cout << "\tEmail:\t " << email << endl;
				cout << "\tMobile:\t " << mobile << endl;
				cout << "\tHome:\t " << home << endl;
				tmp = "yep";
			}
		}
		else if (searchIndex == 3) {
			if (case_insensitive_match(address, inputs)) {
				cout << " Record\t" << record << endl;
				cout << "\tName:\t " << name << endl;
				cout << "\tFamily:\t " << family << endl;
				cout << "\tAddress: " << address << endl;
				cout << "\tEmail:\t " << email << endl;
				cout << "\tMobile:\t " << mobile << endl;
				cout << "\tHome:\t " << home << endl;
				tmp = "yep";
			}
		}
		else if (searchIndex == 4) {
			if (case_insensitive_match(email, inputs)) {
				cout << " Record\t" << record << endl;
				cout << "\tName:\t " << name << endl;
				cout << "\tFamily:\t " << family << endl;
				cout << "\tAddress: " << address << endl;
				cout << "\tEmail:\t " << email << endl;
				cout << "\tMobile:\t " << mobile << endl;
				cout << "\tHome:\t " << home << endl;
				tmp = "yep";
			}
		}
		else if (searchIndex == 5) {
			if ((case_insensitive_match(mobile, inputs)) || (case_insensitive_match(home, inputs))) {
				cout << " Record\t" << record << endl;
				cout << "\tName:\t " << name << endl;
				cout << "\tFamily:\t " << family << endl;
				cout << "\tAddress: " << address << endl;
				cout << "\tEmail:\t " << email << endl;
				cout << "\tMobile:\t " << mobile << endl;
				cout << "\tHome:\t " << home << endl;
				tmp = "yep";
			}
		}
	}
	dbclose();

	if (tmp == "nope")
		cout << "\tNothing found";
	cout << "\n\n";
	system("pause");
}

void recordTemplate::showAll(void)
{
	system("cls");
	record = 0;
	dbin();
	while (!db.eof()) {
		getline(db, name);
		if (db.eof())
			break;
		getline(db, family);
		getline(db, address);
		getline(db, email);
		getline(db, mobile);
		getline(db, home);
		record++;
		cout << " Record\t" << record << endl;
		cout << "\tName:\t " << name << endl;
		cout << "\tFamily:\t " << family << endl;
		cout << "\tAddress: " << address << endl;
		cout << "\tEmail:\t " << email << endl;
		cout << "\tMobile:\t " << mobile << endl;
		cout << "\tHome:\t " << home << "\n\n";
	}
	dbclose();
	cout << endl;
	system("pause");
}

void recordTemplate::dbout(bool atEnd = 0)
{
	if (atEnd)
		db.open("database.db", ios::app);
	else
		db.open("database.db", ios::out);
}

void recordTemplate::dbin(void)
{
	db.open("database.db", ios::in);
}

void recordTemplate::dbclose(void)
{
	db.close();
}
