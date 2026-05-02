#ifndef MODULEKASIAN_H_INCLUDED
#define MODULEKASIAN_H_INCLUDED

void Dodavannya(Reestr*& db, int& count, int& capacity);
void searchnom(Reestr* db, int count);
void loadDatabaseFromFile(Reestr*& db, int& count, int& capacity, string filename = "Reestr.txt");
void saveDatabaseToFile(Reestr* db, int count, string filename = "Reestr.txt");
#endif // MODULEKASIAN_H_INCLUDED
