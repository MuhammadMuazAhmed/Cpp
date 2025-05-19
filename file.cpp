#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX 50

class person
{
protected:
    string name;
    string cnic;

public:
    person(string s = " ", string c = " ") : name(s), cnic(c) {}
    virtual void setter();
    virtual void getter() const;
    virtual bool outstanding() = 0;
    virtual void savetofile(ofstream &file) const = 0;
    virtual void readfromfile(ifstream &file) = 0;
    virtual ~person() {}
};

void person::setter()
{
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter CNIC: ";
    getline(cin, cnic);
}

void person::getter() const
{
    cout << "Name: " << name << endl;
    cout << "CNIC: " << cnic << endl;
}

class teacher : virtual public person
{
    string field;
    int nop;

public:
    teacher(string s = " ", string c = " ", string f = " ", int n = 0) : person(s, c), field(f), nop(n) {}
    void setter();
    void getter() const;
    bool outstanding();
    void savetofile(ofstream &file) const;
    void readfromfile(ifstream &file);
    ~teacher() {}
};

void teacher::setter()
{
    person::setter();
    cout << "Enter No. of publications: ";
    cin >> nop;
    cout << "Enter field: ";
    cin.ignore();
    getline(cin, field);
}

void teacher::getter() const
{
    cout << "TEACHER:" << endl;
    person::getter();
    cout << "No. of publications: " << nop << endl;
    cout << "Field: " << field << endl;
}

bool teacher::outstanding()
{
    return nop > 7;
}

void teacher::savetofile(ofstream &file) const
{
    file << "T " << name << endl
         << cnic << endl
         << nop << endl
         << field << endl;
}

void teacher::readfromfile(ifstream &file)
{
    file.ignore(); // Consume newline
    getline(file, name);
    getline(file, cnic);
    file >> nop;
    file.ignore(); // Consume newline
    getline(file, field);
}

class student : virtual public person
{
    string degree;
    float cgpa;

public:
    student(string s = " ", string c = " ", string d = " ", float g = 0.0) : person(s, c), degree(d), cgpa(g) {}
    void setter();
    void getter() const;
    bool outstanding();
    void savetofile(ofstream &file) const;
    void readfromfile(ifstream &file);
    ~student() {}
};

void student::setter()
{
    person::setter();
    cout << "Enter CGPA: ";
    cin >> cgpa;
    cout << "Enter degree: ";
    cin.ignore();
    getline(cin, degree);
}

void student::getter() const
{
    cout << "STUDENT:" << endl;
    person::getter();
    cout << "CGPA: " << cgpa << endl;
    cout << "Degree: " << degree << endl;
}

bool student::outstanding()
{
    return cgpa > 3.0;
}

void student::savetofile(ofstream &file) const
{
    file << "S " << name << endl
         << cnic << endl
         << cgpa << endl
         << degree << endl;
}

void student::readfromfile(ifstream &file)
{
    file.ignore(); // Consume newline
    getline(file, name);
    getline(file, cnic);
    file >> cgpa;
    file.ignore(); // Consume newline
    getline(file, degree);
}

// Function to store data in an array after reading from the file
void storeDataInArray(person *personArray[MAX], int &personCount, ifstream &file)
{
    personCount = 0;
    char type;
    while (file >> type)
    {
        if (type == 'T')
        {
            personArray[personCount] = new teacher;
            personArray[personCount++]->readfromfile(file);
        }
        else if (type == 'S')
        {
            personArray[personCount] = new student;
            personArray[personCount++]->readfromfile(file);
        }
    }
    cout << "Data stored in array successfully." << endl;
}

int main()
{
    person *p[MAX];
    int count = 0;
    int t = 0;
    int s = 0;
    int t_outstanding = 0;
    int s_outstanding = 0;
    person *personArray[MAX];
    int personCount = 0;
    ofstream file;
    ifstream infile;

    do
    {
        cout << "\nMain Menu:" << endl;
        cout << "1. Create Teacher Obj To Store Data" << endl;
        cout << "2. Create Student Obj To Store Data" << endl;
        cout << "3. Display Record" << endl;
        cout << "4. Display Stats" << endl;
        cout << "5. Teacher Display" << endl;
        cout << "6. Student Display" << endl;
        cout << "7. Save Data to file" << endl;
        cout << "8. Read Data from file" << endl;
        cout << "9 .Exit" << endl;
        cout << "Enter your choice: ";

        int ch;
        if (!(cin >> ch))
        {
            cout << "Enter a valid choice" << endl;
            cin.clear();
            while (cin.get() != '\n')
            {
            } // Consume the entire line.
            continue;
        }

        switch (ch)
        {
        case 1:
            p[count] = new teacher;
            p[count++]->setter();
            t++;
            break;
        case 2:
            p[count] = new student;
            p[count++]->setter();
            s++;
            break;
        case 3:
            for (int i = 0; i < count; i++)
            {
                p[i]->getter();
                if (typeid(*p[i]) == typeid(teacher) && p[i]->outstanding())
                {
                    cout << "Outstanding Teacher" << endl;
                }
                else if (typeid(*p[i]) == typeid(student) && p[i]->outstanding())
                {
                    cout << "Outstanding Student" << endl;
                }
                cout << endl;
            }
            break;
        case 4:
            cout << "No. of teachers: " << t << endl;
            cout << "No. of students: " << s << endl;
            for (int i = 0; i < count; i++)
            {
                if (typeid(*p[i]) == typeid(teacher) && p[i]->outstanding())
                {
                    t_outstanding++;
                }
                else if (typeid(*p[i]) == typeid(student) && p[i]->outstanding())
                {
                    s_outstanding++;
                }
                cout << endl;
            }
            cout << "No. of outstanding students:" << s_outstanding << endl;
            cout << "No. of outstanding teachers:" << t_outstanding << endl;
            break;
        case 5:
            for (int i = 0; i < count; i++)
            {
                if (typeid(*p[i]) == typeid(teacher))
                {
                    p[i]->getter();
                }
            }
            break;
        case 6:
            for (int i = 0; i < count; i++)
            {
                if (typeid(*p[i]) == typeid(student))
                {
                    p[i]->getter();
                }
            }
            break;
        case 7:
            file.open("personinfo.txt", ios::out | ios::app);
            if (!file)
            {
                cout << "Unable to open file";
                exit(1);
            }
            for (int i = 0; i < count; i++)
            {
                p[i]->savetofile(file);
                delete p[i];
                --count;
            }
            file.close();
            break;
        case 8:
            // Open the file before reading
            infile.open("personinfo.txt", ios::in);
            if (!infile)
            {
                cout << "Unable to open file";
                exit(1);
            }

            storeDataInArray(personArray, personCount, infile);

            // Close the file after reading
            infile.close();

            for (int i = 0; i < personCount; i++)
            {
                personArray[i]->getter();
            }
            break;

        case 9:
            // Clean up memory before exiting
            for (int i = 0; i < count; i++)
            {
                delete p[i];
            }
            // Clean up dynamically allocated memory
            for (int i = 0; i < personCount; i++)
            {
                delete personArray[i];
            }
            return 0;
        default:
            cout << "Invalid Option" << endl;
        }
    } while (true);

    return 0;
}
