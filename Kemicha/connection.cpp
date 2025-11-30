            #include "connection.h"
            #include <QMessageBox>
            connection::connection()
            {

            }

            bool connection::createconnect()
            {bool test=false;
                QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
                db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données
                db.setUserName("emna");//ins                                                                                                                                                                                                                                                                                                                                                                                                                                                                                erer nom de l'utilisateur
                db.setPassword("1234");//inserer mot de passe de cet utilisateur

                if (db.open())
                    test=true;





                return  test;
            }
