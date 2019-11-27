#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->map.load_stadiums("american.txt");
    this->map.load_stadiums("national.txt");
    this->map.load_edges("edges.prn");
    this->stadiums = this->map.get_stadiums();
    for (unsigned int i = 0; i < this->stadiums.size(); ++i)
        ui->stadium_list->addItem(QString::fromStdString(this->stadiums[i].name));
    this->load_souvenirs("souvenirs.txt");

    /************************* CONNECTIONS *******************************/

    // update currently selected items
    connect(ui->stadium_list, SIGNAL(itemSelectionChanged()), this, SLOT(currently_selected_stadium()));


    // personal trip
    connect(ui->plan_trip_add_to_path_button, SIGNAL(clicked(bool)), this, SLOT(add_stadium_to_path()));
    connect(ui->plan_trip_confirm_button, SIGNAL(clicked(bool)), this, SLOT(plan_trip()));

    // all major league
    connect(ui->trip_major_league_button, SIGNAL(clicked(bool)), this, SLOT(trip_to_all_major_league_stadiums()));

    // all american league
    connect(ui->trip_american_league_button, SIGNAL(clicked(bool)), this, SLOT(trip_to_all_american_league_stadiums()));

    // all national league
    connect(ui->trip_national_league_button, SIGNAL(clicked(bool)), this, SLOT(trip_to_all_national_league_stadiums()));

    // view stadium info
    connect(ui->view_stadium_info_confirm_button, SIGNAL(clicked(bool)), this, SLOT(view_stadium_information()));

    // modify stadium
    connect(ui->change_stadium_name_confirm_button, SIGNAL(clicked(bool)), this, SLOT(change_stadium_name()));
    connect(ui->add_team_confirm_button, SIGNAL(clicked(bool)), this, SLOT(add_team()));
    connect(ui->remove_team_confirm_button, SIGNAL(clicked(bool)), this, SLOT(remove_team()));

    // add stadium
    connect(ui->add_stadium_confirm_button, SIGNAL(clicked(bool)), this, SLOT(add_stadium()));

    // shortest distance
    connect(ui->shortest_distance_confirm_button, SIGNAL(clicked(bool)), this, SLOT(shortest_distance()));

    // modify souvenirs
    connect(ui->add_souvenir_confirm_button, SIGNAL(clicked(bool)), this, SLOT(add_souvenir()));
    connect(ui->remove_souvenir_confirm_button, SIGNAL(clicked(bool)), this, SLOT(remove_souvenir()));
    connect(ui->modify_souvenir_confirm_button, SIGNAL(clicked(bool)), this, SLOT(modify_souvenir()));

    // switch main pages
    connect(ui->plan_a_trip_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_plan_a_trip()));
    connect(ui->trip_american_league_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_blank_page()));
    connect(ui->trip_national_league_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_blank_page()));
    connect(ui->trip_major_league_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_blank_page()));
    connect(ui->view_stadium_information_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_view_stadium_information()));
    connect(ui->shortest_distance_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_shortest_distance()));
    connect(ui->modify_stadium_information_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_modify_stadium_information()));
    connect(ui->modify_souvenir_list_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_modify_souvenir_list()));
    connect(ui->add_stadium_button, SIGNAL(clicked(bool)), this, SLOT(switch_to_add_stadium()));

    // switch souvenir pages
    connect(ui->add_souvenir_radio_button, SIGNAL(toggled(bool)), this, SLOT(switch_to_add_souvenir()));
    connect(ui->remove_souvenir_radio_button, SIGNAL(toggled(bool)), this, SLOT(switch_to_remove_souvenir()));
    connect(ui->modify_souvenir_radio_button, SIGNAL(toggled(bool)), this, SLOT(switch_to_modify_souvenir()));
    connect(ui->pages, SIGNAL(currentChanged(int)), this, SLOT(switch_souvenir_options_to_blank_page()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_souvenirs(string file)    // IN: souvenir list file
{
    ifstream in_file;                       // IN: ifstream variable

    // OUTPUT: open the given souvenir list file
    in_file.open(file);
    if (!in_file)
    {
        cout << "ERROR: souvenirs.txt not opened" << endl;
        exit(0);
    }

    string name;                            // IN: name of souvenir
    double price;                           // IN: price of souvenir

    // OUTPUT: add each souvenir to the souvenir list
    while (getline(in_file, name))
    {
        in_file >> price;
        this->souvenirs.push_back(Souvenir(name, price));
        in_file.ignore(1000, '\n');
    }
    for (unsigned int i = 0; i < this->souvenirs.size(); ++i)
        ui->souvenir_list->addItem(QString::fromStdString(this->souvenirs[i].name));
}

// PRIVATE SLOTS
void MainWindow::currently_selected_stadium()
{
    QString name;                   // IN: name of currently selected stadium

    // OUTPUT: if none are currently selected, use the first item in the list
    if (ui->stadium_list->currentItem() == nullptr)
        name = QString::fromStdString(this->stadiums[0].name);
    else
        name = ui->stadium_list->currentItem()->text();

    ui->view_stadium_info_line_edit->setText(name);
    ui->modify_stadium_info_line_edit->setText(name);
    ui->plan_trip_starting_stadium->setText(name);

    ui->remove_team_combobox->clear();
    Stadium* stadium = map.get_stadium(name.toStdString());
    for (unsigned int i = 0; i < stadium->teams.size(); ++i)
        ui->remove_team_combobox->addItem(QString::fromStdString(stadium->teams[i]));
}

void MainWindow::plan_trip()
{
    string name = ui->stadium_list->currentItem()->text().toStdString();
    int start = ui->stadium_list->currentIndex().row();
    this->personal_trip_selected_stadiums.insert(start);

    vector<int> temp = this->map.trip(name, this->personal_trip_selected_stadiums);

    QString output = QString::fromStdString(this->map.get_path(temp)) + "\n\n";
    output += "Number of stadiums visited: " + QString::number(temp.size()) + '\n';
    output += "Total Distance: " + QString::number(this->map.total_distance(temp));
    ui->output_box->setPlainText(output);

    this->personal_trip_selected_stadiums.clear();
    ui->plan_trip_selected_stadiums->setText("Selected Stadiums: ");
    ui->plan_trip_add_to_path_combobox->clear();
    for (unsigned int i = 0; i < this->stadiums.size(); ++i)
        ui->plan_trip_add_to_path_combobox->addItem(QString::fromStdString(this->stadiums[i].name));
}

void MainWindow::add_stadium_to_path()
{
    QString stadium = ui->plan_trip_add_to_path_combobox->currentText();
    this->personal_trip_selected_stadiums.insert(this->map.get_index(stadium.toStdString()));
    ui->plan_trip_add_to_path_combobox->removeItem(ui->plan_trip_add_to_path_combobox->currentIndex());
    ui->plan_trip_selected_stadiums->setText(ui->plan_trip_selected_stadiums->text() + stadium + " ");
}

void MainWindow::trip_to_all_major_league_stadiums()
{
    set<int> wanted;
    for (unsigned int i = 0; i < this->stadiums.size(); ++i)
        if (this->stadiums[i].league == "Major")
            wanted.insert(i);

    if (wanted.empty())
    {
        ui->output_box->setPlainText("ERROR: No Major League stadiums");
        return;
    }

    // ANGEL STADIUM STARTING
    wanted.insert(0);
    vector<int> temp = this->map.trip("Angel Stadium", wanted);

    QString output = QString::fromStdString(this->map.get_path(temp)) + '\n' + QString::number(this->map.total_distance(temp));
    ui->output_box->setPlainText(output);
}

void MainWindow::trip_to_all_american_league_stadiums()
{
    set<int> wanted;
    for (unsigned int i = 0; i < this->stadiums.size(); ++i)
        if (this->stadiums[i].league == "American")
            wanted.insert(i);

    if (wanted.empty())
    {
        ui->output_box->setPlainText("ERROR: No American League stadiums");
        return;
    }

    // ANGEL STADIUM STARTING
    wanted.insert(0);
    vector<int> temp = this->map.trip("Angel Stadium", wanted);

    QString output = QString::fromStdString(this->map.get_path(temp)) + "\n\n";
    output += "Number of stadiums visited: " + QString::number(temp.size()) + '\n';
    output += "Total Distance: " + QString::number(this->map.total_distance(temp));
    ui->output_box->setPlainText(output);
}

void MainWindow::trip_to_all_national_league_stadiums()
{
    set<int> wanted;
    for (unsigned int i = 0; i < this->stadiums.size(); ++i)
        if (this->stadiums[i].league == "National")
            wanted.insert(i);

    if (wanted.empty())
    {
        ui->output_box->setPlainText("ERROR: No National League stadiums");
        return;
    }

    // ANGEL STADIUM STARTING
    wanted.insert(0);
    vector<int> temp = this->map.trip("Angel Stadium", wanted);

    QString output = QString::fromStdString(this->map.get_path(temp)) + "\n\n";
    output += "Number of stadiums visited: " + QString::number(temp.size()) + '\n';
    output += "Total Distance: " + QString::number(this->map.total_distance(temp));
    ui->output_box->setPlainText(output);
}

void MainWindow::view_stadium_information()
{
    string name = ui->view_stadium_info_line_edit->text().toStdString();
    Stadium* stadium = this->map.get_stadium(name);

    QString output =
        "Name: " + QString::fromStdString(stadium->name) + '\n' +
        "League: " + QString::fromStdString(stadium->league) + '\n' +
        "Address: " + QString::fromStdString(stadium->address) + '\n' +
        "Box Office Number: " + QString::fromStdString(stadium->box_office_number) + '\n' +
        "Date Opened: " + QString::fromStdString(stadium->date_opened) + '\n' +
        "Seating Capacity: " + QString::fromStdString(stadium->seating_capacity) + '\n' +
        "Teams: ";
    for (unsigned int i = 0; i < stadium->teams.size(); ++i)
    {
        if (i + 1 >= stadium->teams.size())
            output += QString::fromStdString(stadium->teams[i]);
        else
            output += QString::fromStdString(stadium->teams[i]) + ", ";
    }
    output += '\n';

    ui->output_box->setPlainText(output);
}

void MainWindow::change_stadium_name()
{
    string old_name = ui->modify_stadium_info_line_edit->text().toStdString();
    string new_name = ui->change_stadium_name_line_edit->text().toStdString();
    Stadium* stadium = this->map.get_stadium(old_name);
    int index = this->map.get_index(old_name);

    stadium->name = new_name;
    this->stadiums[index].name = new_name;

    ui->output_box->setPlainText("Successfully updated stadium name to: " +
                                 QString::fromStdString(new_name));
}

void MainWindow::add_team()
{
    string name = ui->modify_stadium_info_line_edit->text().toStdString();
    string new_team = ui->add_team_line_edit->text().toStdString();
    Stadium* stadium = map.get_stadium(name);

    stadium->add_team(new_team);

    ui->remove_team_combobox->addItem(QString::fromStdString(new_team));

    ui->output_box->setPlainText("Successfully added team (" +
                                 QString::fromStdString(new_team) +
                                 ") to stadium (" +
                                 QString::fromStdString(name) + ")");
}

void MainWindow::remove_team()
{
    if (ui->remove_team_combobox->count() != 0)
    {
        string name = ui->modify_stadium_info_line_edit->text().toStdString();
        QString team_name = ui->remove_team_combobox->currentText();
        int team = ui->remove_team_combobox->currentIndex();
        Stadium* stadium = map.get_stadium(name);

        stadium->remove_team(team);

        ui->remove_team_combobox->clear();
        for (unsigned int i = 0; i < stadium->teams.size(); ++i)
            ui->remove_team_combobox->addItem(QString::fromStdString(stadium->teams[i]));

        ui->output_box->setPlainText("Successfully removed team " +
                                     QString::fromStdString(name) +
                                     team_name + " from stadium(" +
                                     QString::fromStdString(name) + ")");
    }
    else
        ui->output_box->setPlainText("ERROR: this stadium currently has no teams");
}

void MainWindow::add_stadium()
{
    string name = ui->add_stadium_name->text().toStdString();
    string team = ui->add_stadium_team->text().toStdString();
    string address = ui->add_stadium_address->text().toStdString();
    string league = ui->add_stadium_league->currentText().toStdString();
    string box_office_number = ui->add_stadium_box_office_number->text().toStdString();
    string date_opened = ui->add_stadium_date_opened->text().toStdString();
    string seating_capacity = ui->add_stadium_seating_capacity->text().toStdString();
    this->map.add_stadium(Stadium(name, team, address, box_office_number, date_opened, seating_capacity, league));
    this->stadiums = this->map.get_stadiums();

    ui->stadium_list->addItem(QString::fromStdString(name));

    ui->output_box->setPlainText("Successfully added stadium (" + QString::fromStdString(name) + ")");
}

void MainWindow::add_souvenir()
{
    string name = ui->add_souvenir_line_edit->text().toStdString();
    double price = ui->add_souvenir_spinbox->value();
    this->souvenirs.push_back(Souvenir(name, price));
    ui->souvenir_list->addItem(QString::fromStdString(name));

    ui->output_box->setPlainText("Successfully added " +
                                 QString::fromStdString(name) +
                                 " to souvenir list");
}

void MainWindow::remove_souvenir()
{
    if (ui->souvenir_list->count() != 0)
    {
        int index = ui->souvenir_list->currentRow();
        QString name = ui->souvenir_list->currentItem()->text();
        this->souvenirs.erase(this->souvenirs.begin() + index);
        ui->souvenir_list->takeItem(index);

        ui->output_box->setPlainText("Successfully removed " + name +
                                     " from souvenir list");
    }
    else
        ui->output_box->setPlainText("ERROR: souvenir list is empty");
}

void MainWindow::modify_souvenir()
{
    if (ui->souvenir_list->count() != 0)
    {
        int index = ui->souvenir_list->currentRow();
        QString old_name = ui->souvenir_list->currentItem()->text();
        QString new_name = ui->modify_souvenir_line_edit->text();
        double old_price = this->souvenirs.at(index).price;
        double new_price = ui->modify_souvenir_spinbox->value();

        this->souvenirs.at(index).name = new_name.toStdString();
        this->souvenirs.at(index).price = new_price;

        ui->output_box->setPlainText("Successfully modified souvenir: " +
                                     old_name + ", " + old_price + "-> " +
                                     new_name + ", " + new_price);
    }
    else
        ui->output_box->setPlainText("ERROR: souvenir list is empty");
}

void MainWindow::shortest_distance()
{
    vector<int> shortest_path;

    int stadium1 = ui->shortest_distance_stadium_1_combobox->currentIndex();
    int stadium2 = ui->shortest_distance_stadium_2_combobox->currentIndex();

    vector<int> paths = this->map.dijkstra(stadium1);


    int temp = stadium2;

    while (paths[temp] != -1)
    {
        shortest_path.push_back(temp);
        temp = paths[temp];
    }
    shortest_path.push_back(stadium1);

    std::reverse(shortest_path.begin(), shortest_path.end());

    for (unsigned int i = 0; i < shortest_path.size(); ++i)
        cout << shortest_path[i] << " ";

    QString output;

    output += QString::fromStdString(this->map.get_path(shortest_path)) + '\n';
    output += "Total distance: " + QString::number(this->map.total_distance(shortest_path));

    ui->output_box->setPlainText(output);
}

void MainWindow::switch_to_blank_page()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::switch_to_plan_a_trip()
{
    ui->plan_trip_add_to_path_combobox->clear();
    for (unsigned int i = 0; i < this->stadiums.size(); ++i)
        ui->plan_trip_add_to_path_combobox->addItem(QString::fromStdString(this->stadiums[i].name));
    ui->pages->setCurrentIndex(1);
}

void MainWindow::switch_to_view_stadium_information()
{
    ui->pages->setCurrentIndex(2);
}

void MainWindow::switch_to_shortest_distance()
{
    ui->shortest_distance_stadium_1_combobox->clear();
    ui->shortest_distance_stadium_2_combobox->clear();

    for (unsigned int i = 0; i < this->stadiums.size(); ++i)
    {
        ui->shortest_distance_stadium_1_combobox->addItem(QString::fromStdString(this->stadiums[i].name));
        ui->shortest_distance_stadium_2_combobox->addItem(QString::fromStdString(this->stadiums[i].name));
    }

    ui->pages->setCurrentIndex(3);
}

void MainWindow::switch_to_modify_stadium_information()
{
    ui->pages->setCurrentIndex(4);
}

void MainWindow::switch_to_modify_souvenir_list()
{
    ui->pages->setCurrentIndex(5);
}

void MainWindow::switch_to_add_stadium()
{
    ui->pages->setCurrentIndex(6);
}

void MainWindow::switch_souvenir_options_to_blank_page()
{
    if (ui->add_souvenir_radio_button->isChecked() ||
        ui->remove_souvenir_radio_button->isChecked() ||
        ui->modify_souvenir_radio_button->isChecked())
            return;
    ui->souvenir_modifications->setCurrentIndex(0);
}

void MainWindow::switch_to_add_souvenir()
{
    ui->souvenir_modifications->setCurrentIndex(1);
}

void MainWindow::switch_to_remove_souvenir()
{
    ui->souvenir_modifications->setCurrentIndex(2);
}

void MainWindow::switch_to_modify_souvenir()
{
    ui->souvenir_modifications->setCurrentIndex(3);
}
