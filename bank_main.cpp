#include "bank_main.h"
#include "ui_bank_main.h"
#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
Bank_Main::Bank_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Bank_Main)
{
    ui->setupUi(this);
    QPixmap pix_login(":/icons/icons/login.png"); //obiekt, który przechowuję ścieżkę do ikonki z folderu "Zasoby/resources"
    ui->label_login->setPixmap(pix_login); //ustawiam na etykietę "label_login" zdjęcie, które ma się wyświetlać
    QPixmap pix_password(":/icons/icons/password_login.png"); //obiekt, który przechowuję ścieżkę do ikonki z folderu "Zasoby/resources"
    ui->label_password->setPixmap(pix_password); //ustawiam na etykietę "label_password" zdjęcie, które ma się wyświetlać
    QPixmap pix_bank(":/icons/icons/bank_main.png"); //obiekt, który przechowuję ścieżkę do ikonki z folderu "Zasoby/resources"
    ui->label_bank_pic->setPixmap(pix_bank); //ustawiam na etykietę "label_bank_pic" zdjęcie, które ma się wyświetlać
    this->setFixedSize(QSize(800, 600)); //ustawia rozmiar okienka logowania na nieskalowalny
    this->setStyleSheet("background-color: grey");
    ui->lineEdit_login->setStyleSheet("background-color: white");
    ui->lineEdit_password->setStyleSheet("background-color: white");
}

Bank_Main::~Bank_Main()
{
    delete ui;
}

void Bank_Main::checkLoginAndPassword()
{
    QString login = ui->lineEdit_login->text(); //pobieram tekst, który jest wpisywany w "lineEdit_login"
    QString password = ui->lineEdit_password->text(); //pobieram tekst, który jest wpisywany w "lineEdit_password"
    QFile file(":/accounts/Konta/"+login+"/login_password.txt"); //obiekt ze ścieżką do pliku
    if(!file.open(QFile::ReadOnly | QFile::Text)) //precyzuję jakie pliki otwieram
    {
        QMessageBox::warning(this, "warning", "Błędna nazwa użytkownika!");
        ui->lineEdit_login->clear();
        ui->lineEdit_password->clear();
    }
    else
    {
        int numberOfLine=0; //zmienna, która będzie odpowiadała za indeks tablicy
        QTextStream in(&file); //pobiera adres obiektu "file"
        QString loginLine=in.readLine(); //zmienna, do której przypisujemy linijkę z pliku
        QString line[2]; //tablica 2-elementowa typu QString
        while(!loginLine.isNull()) //pętla sprawdzająca, poniższe instrukcję, dopóki plik nie jest pusty
        {
           line[numberOfLine]=in.readLine(); //pierwszy indeks tablicy to pierwsza linijka w pliku tekstowym
           if(login==line[numberOfLine]) //jezeli tekst z loginu (z lineEdit_login, patrz wyżej) jest identyczny jak 1 linijka w pliku, to inkrementujemy numer linii i wchodzimy w kolejnego ifa =)
           numberOfLine++; //inkrementacja indeksu (czyli napisu w pliku tekstowym)
           {
               if(password==line[numberOfLine] && login.count(' ') != login.length() && password.count(' ') != password.length() ) //to samo co wyzej + sprawdzam, czy login i haslo nie jest puste, a nastepnie po spelnieniu warunku, chowamy glowny ekran logowania, tworzymy instancję, a następnie za pomocą polimorficznego wskaźnika odpalamy menu glowne
               {
                   hide();
                   bankMenu = new Bank_Menu(this, login);
                   bankMenu->setAttribute( Qt::WA_DeleteOnClose );
                   bankMenu->show();

                   break; //wychodzimy z pętli
               }
               else //w przeciwnym wypadku pokazuje się komunikat, o złym loginie i haśle
               {
                  QMessageBox::information(this, "Zaloguj","Hasło jest niepoprawne! Wpisz jeszcze raz");
                  ui->lineEdit_login->clear(); //czyszczę pole tekstowe
                  ui->lineEdit_password->clear(); //czyszczę pole tekstowe
                  break; //wychodzę z pętli
               }

           }

        }
    }
    file.close(); //zamykamy plik
}
void Bank_Main::on_pushButton_zaloguj_clicked() //metoda powodująca odpalenie powyższej metody (checkLoginAndPassword)
{
    checkLoginAndPassword();
}

