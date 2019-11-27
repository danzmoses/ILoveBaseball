#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"
#include "souvenir.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixMap>
#include <fstream>
#include <stack>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();


        void load_souvenirs(string file);

    private:
        Ui::MainWindow *ui;
        Map map;
        vector<Stadium> stadiums;
        vector<Souvenir> souvenirs;
        set<int> personal_trip_selected_stadiums;

    private slots:
        // main functions
        void plan_trip();
        void trip_to_all_major_league_stadiums();
        void trip_to_all_american_league_stadiums();
        void trip_to_all_national_league_stadiums();
        void view_stadium_information();
        void change_stadium_name();
        void add_team();
        void remove_team();
        void add_souvenir();
        void remove_souvenir();
        void modify_souvenir();
        void add_stadium();
        void shortest_distance();

        // main pages
        void switch_to_blank_page();
        void switch_to_plan_a_trip();
        void switch_to_view_stadium_information();
        void switch_to_shortest_distance();
        void switch_to_modify_stadium_information();
        void switch_to_modify_souvenir_list();
        void switch_to_add_stadium();

        // souvenir pages
        void switch_to_add_souvenir();
        void switch_to_remove_souvenir();
        void switch_to_modify_souvenir();
        void switch_souvenir_options_to_blank_page();

        void add_stadium_to_path();
        void currently_selected_stadium();
};

#endif // MAINWINDOW_H
