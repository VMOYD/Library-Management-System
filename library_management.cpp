#include <iostream>    //Basic input output 
#include <iomanip>     //to format the text setw and all 
#include <curses.h>    //for getch() to hold the screen 
#include <string.h>    //function related to string 
#include <fstream>     //file related function 
using namespace std;
#define label cout << "<----------------LIBRARY MANAGEMENT SYSTEM---------------->\n\n";
const int y = 50, x = 20;
class library
{
public:
    int b_ava, t_av_book;
    char b_name[100], b_id[20], i_date[10], st_id[20];
    ofstream ofs;
    ifstream ifs;
    void view_books();
    void search_book();
};

class librarian : public library
{
public:
    void modify();
    void changepass();
};
class issue : public librarian
{
public:
    void issue_book();
    void view_issue_book();
    void search_student();
    void reissue();
    void return_book();
};

void library::view_books()
{
    ifs.open("book_details.txt");
    if (!ifs)
    {
        cout << "\n Data not found \n";
        return;
    }
    cout << left << setw(x)
         << "BOOK ID"
         << left << setw(x)
         << "BOOK NAME"
         << left << setw(x)
         << "AVAILABLE"
         << left << setw(x)
         << "TOTAL BOOK" << endl;
    while (ifs >> b_id >> b_name >> b_ava >> t_av_book)
    {
        cout << left << setw(x)
             << b_id
             << left << setw(x)
             << b_name
             << left << setw(x)
             << b_ava
             << left << setw(x)
             << t_av_book << endl;
    }
    ifs.close();
    return;
}

void library::search_book()
{
    int ch;
search_menu:
    cout << "\n* 1 * By book name\n* 2 * By book id\n Enter your choice :  ";
    cin >> ch;
    ifs.open("book_details.txt");
    if (!ifs)
    {
        cout << "\n Data not found \n";
        return;
    }
    char s_name[100], s_id[20];
    switch (ch)
    {
    case 1:
        cout << "\nenter the name : ";
        cin >> s_name;
        break;
    case 2:
        cout << "\nenter the book id :";
        cin >> s_id;
        break;
    default:
        cout << "\nwrong choice : ";
        goto search_menu;
    }
    int flag = 0;
    cout << left << setw(x)
         << "BOOK ID"
         << left << setw(x)
         << "BOOK NAME"
         << left << setw(x)
         << "AVAILABLE"
         << left << setw(x)
         << "TOTAL BOOK" << endl;
    while (ifs >> b_id >> b_name >> b_ava >> t_av_book)
    {
        if (ch == 1 && strcmp(b_name, s_name) == 0)
        {
            flag = 1;
            cout << left << setw(x)
                 << b_id
                 << left << setw(x)
                 << b_name
                 << left << setw(x)
                 << b_ava
                 << left << setw(x)
                 << t_av_book << endl;
        }
        else if (ch == 2 && strcmp(b_id, s_id) == 0)
        {
            flag = 1;
            cout << left << setw(x)
                 << b_id
                 << left << setw(x)
                 << b_name
                 << left << setw(x)
                 << b_ava
                 << left << setw(x)
                 << t_av_book << endl;
        }
        else
        {
            continue;
        }
    }
    if (flag == 0)
        cout << "\nNOT FOUND\n";
    ifs.close();
}

void librarian::modify()
{
    int ch;
    cout << "\n1.add book\n2.modify\nenter your choice : ";
    cin >> ch;
    if (ch == 1)
    {
        ofs.open("book_details.txt", ios::app);
        cout << "\nenter book id : ";
        cin >> b_id;
        cout << "\nenter book name : ";
        cin >> b_name;
        cout << "\nenter quantity : ";
        cin >> b_ava;
        ofs << b_id << " " << b_name << " " << b_ava << " " << b_ava << "\n";
        ofs.close();
    }
    else if (ch == 2)
    {
        char m_b_name[20];
        int flag = 0;
        cout << "\n1.by book name\n2.by book id\nenter your choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\nenter the book name : ";
            cin >> m_b_name;
            break;
        case 2:
            cout << "\nenter the book id : ";
            cin >> m_b_name;
            break;
        }
        if (!ofs)
        {
            cout << "error file not open";
            return;
        }
        ifs.open("book_details.txt");
        ofs.open("temp.txt");
        while (ifs >> b_id >> b_name >> b_ava >> t_av_book)
        {
            if (strcmp(b_name, m_b_name) == 0)
            {
                flag = 1;
                cout << "enter new quantity ";
                cin >> t_av_book;
            }
            ofs << b_id << " " << b_name << " " << b_ava << " " << t_av_book << "\n";
        }
        ofs.close();
        ifs.close();
        char newname[] = "book_details.txt";
        char oldname[] = "temp.txt";
        remove(newname);
        rename(oldname, newname);
        if (flag == 0)
        {
            cout << "NOT FOUND\n";
        }
        else
        {
            cout << "UPDATED\n";
        }
    }
}
void librarian::changepass()
{
    char txt[20];
    ofs.open("software_detail.dat", ios::binary | ios::out);
    if (!ofs)
    {
        cout << "Cannot open file!" << endl;
        return;
    }
    cout << "enter the pass ";
    cin >> txt;
    ofs.write((char *)&txt, sizeof(txt));
    ofs.close();
    cout << "password changed restart the application";
}
void issue::issue_book()
{
    int flag = 0;
    char t_b_id[20];
    cout << "enter book id you want to issue : ";
    cin >> t_b_id;
    cout << "enter the student id : ";
    cin >> st_id;
    time_t now = time(0);
    ifs.open("book_details.txt");
    ofs.open("issue.txt", ios::app);
    while (ifs >> b_id >> b_name >> b_ava >> t_av_book)
    {
        if (strcmp(b_id, t_b_id) == 0)
        {
            flag = 1;
            if (b_ava == 0)
            {
                cout << "book is not available ";
                ifs.close();
                ofs.close();
                break;
            }
            else
            {
                time_t now = time(NULL);
                ofs << b_id << " " << b_name << " " << now << " " << st_id << "\n";
                ofs.close();
                ifstream ifs1;
                ofstream ofs1;
                ifs.close();
                ifs1.open("book_details.txt");
                ofs1.open("temp2.txt");
                char xb_id[20], xb_name[20];
                int xb_ava, xt_av_book;
                while (ifs1 >> xb_id >> xb_name >> xb_ava >> xt_av_book)
                {
                    if (strcmp(t_b_id, xb_id) == 0)
                    {
                        xb_ava--;
                    }
                    ofs1 << xb_id << " " << xb_name << " " << xb_ava << " " << xt_av_book << "\n";
                }
                ofs1.close();
                ifs1.close();
                char newname[] = "book_details.txt";
                char oldname[] = "temp2.txt";
                remove(newname);
                rename(oldname, newname);

                cout << "\nISSUED\n";
                break;
            }
        }
    }
    if (flag == 0)
    {
        cout << "BOOK NOT FOUND\n";
    }
}
void issue::view_issue_book()
{
    cout << endl;
    ifs.open("issue.txt");
    time_t now;
    cout << left << setw(x)
         << "BOOK ID"
         << left << setw(x)
         << "BOOK NAME"
         << left << setw(x)
         << "STUDENT ID"
         << left << setw(x)
         << "DATE AND TIME" << endl;
    while (ifs >> b_id >> b_name >> now >> st_id)
    {
        cout << "";
        char *date_time = ctime(&now);
        cout << left << setw(x)
             << b_id
             << left << setw(x)
             << b_name
             << left << setw(x)
             << st_id
             << left << setw(x)
             << date_time;
    }
    ifs.close();
}
void issue::search_student()
{
    int flag = 0;
    char t_st_id[20];
    ifs.open("issue.txt");
    cout << "enter student id your want to search : ";
    cin >> t_st_id;
    time_t now;
    cout << left << setw(x)
         << "BOOK ID"
         << left << setw(x)
         << "BOOK NAME"
         << left << setw(x)
         << "STUDENT ID"
         << left << setw(x)
         << "DATE AND TIME" << endl;
    while (ifs >> b_id >> b_name >> now >> st_id)
    {
        if (strcmp(st_id, t_st_id) == 0)
        {
            char *date_time = ctime(&now);
            flag = 1;
            cout << left << setw(x)
                 << b_id
                 << left << setw(x)
                 << b_name
                 << left << setw(x)
                 << st_id
                 << left << setw(x)
                 << date_time;
        }
    }
    ifs.close();
    if (flag == 0)
    {
        cout << "\nnot found\n";
    }
}
void issue::return_book()
{
    time_t now;
    char t_st_id[20], t_b_id[20];
    cout << "enter the book id you want to return : ";
    cin >> t_b_id;
    cout << "enter student id also : ";
    cin >> t_st_id;
    ifs.open("issue.txt");
    ofs.open("temp.txt");
    int counter = 0;
    while (ifs >> b_id >> b_name >> now >> st_id)
    {
        if ((strcmp(b_id, t_b_id) == 0) && strcmp(t_st_id, st_id) == 0)
        {
            counter++;
        }
        else
        {
            ofs << b_id << " " << b_name << " " << now << " " << st_id << "\n";
        }
    }
    ifs.close();
    ofs.close();
    remove("issue.txt");
    rename("temp.txt", "issue.txt");
    ifs.open("book_details.txt");
    ofs.open("temp.txt");
    char xb_id[20], xb_name[20];
    int xb_ava, xt_av_book;
    while (ifs >> xb_id >> xb_name >> xb_ava >> t_av_book)
    {
        if (strcmp(b_id, t_b_id) == 0)
        {
            cout << "\nx\n";
            xb_ava += counter;
        }
        ofs << xb_id << " " << xb_name << " " << xb_ava << " " << t_av_book << "\n";
    }
    ofs.close();
    ifs.close();
    char newname[] = "book_details.txt";
    char oldname[] = "temp.txt";
    remove(newname);
    rename(oldname, newname);
}
void issue::reissue()
{
    time_t now;
    char t_b_id[20], t_st_id[20];
    cout << "enter the book id you want to reissue";
    cin >> t_b_id;
    cout << "enter the student id : ";
    cin >> t_st_id;
    ifs.open("issue.txt");
    ofs.open("temp.txt");
    while (ifs >> b_id >> b_name >> now >> st_id)
    {
        if ((strcmp(b_id, t_b_id) == 0) && (strcmp(t_st_id, st_id) == 0))
        {
            now = time(NULL);
        }
        ofs << b_id << " " << b_name << " " << now << " " << st_id << "\n";
    }
    ifs.close();
    ofs.close();
    remove("issue.txt");
    rename("temp.txt", "issue.txt");
}
int main()
{
    int choice;
    char pass[20];
    ifstream iss;
main_menu:
    system("cls");
    label;
    cout << "1.Student\n2.Librarian\n3.Close Application\n\nenter your choice : ";
    cin >> choice;
    system("cls");
    library l1;
    issue i1;
    switch (choice)
    {
    case 1:
    student_menu:
        label;
        cout << "\n1.view booklist\n2.search for a book\n3.main menu\n4.close application\nenter your choice :  ";
        cin >> choice;
        system("cls");
        label;
        switch (choice)
        {
        case 1:
            l1.view_books();
            break;
        case 2:
            l1.search_book();
            break;
        case 3:
            goto main_menu;
        case 4:
            exit(1);
        default:
            cout << "wrong choice\n";
        }
        getch();
        system("cls");
        goto student_menu;
        break;
    case 2:
        cout << "\n----------\n\nenter the password : ";
        cin >> pass;
        char txt1[20];
        iss.open("software_detail.dat", ios::binary | ios::in);
        while (iss.eof() == 0)
        {
            iss.read((char *)&txt1, sizeof(txt1));
        }
        if (strcmp(pass, txt1) != 0)
        {
            cout << "\nXXXXXXXX\nwrong password \n ";
            goto main_menu;
        }
    l_menu:
        system("cls");
        label;
        cout << "\n1.view booklist\n2.search for a book\n3.modify/Add book\n4.issue book\n5.main menu\n6.change pass\n7.close application\nenter your choice :  ";
        cin >> choice;
        system("cls");
        label;
        switch (choice)
        {
        case 1:
            i1.view_books();
            break;
        case 2:
            i1.search_book();
            break;
        case 3:
            i1.modify();
            break;
        issue_menu:
        case 4:
            system("cls");
            label;
            cout << "\n1.issue a book\n2.view issued book\n3.search studnet who issued book\n4.reissue book\n5.return book\n6.main menu\n7.close application \nenter your choice : ";
            cin >> choice;
            system("cls");
            label;
            switch (choice)
            {
            case 1:
                i1.issue_book();
                break;
            case 2:
                i1.view_issue_book();
                break;
            case 3:
                i1.search_student();
                break;
            case 4:
                i1.reissue();
                break;
            case 5:
                i1.return_book();
                break;
            case 6:
                goto main_menu;
                break;
            case 7:
                exit(1);
            default:
                cout << "wrong choice";
            }
            getch();
            goto issue_menu;
        case 5:
            goto main_menu;
        case 6:
            i1.changepass();
            break;
        case 7:
            exit(1);
        }
        break;
    case 3:
        exit(1);
    default:
        cout << "wrong choice";
    }
    getch();
    system("cls");
    goto l_menu;
}