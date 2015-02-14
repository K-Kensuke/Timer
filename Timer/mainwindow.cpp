#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"

// 必要な物は自分でincludeすること
#include <QtGui>
#include <QString>
#include <QFile>
#include <QFileDialog>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
// json parsing
#include "picojson.h"

#include <vector>

using namespace std;
using namespace picojson;


void readDataFromFile(QString *filePath, QString *data);
QString filePath = "";
string from = "";
string to = "";
vector<string> weekday(20);
vector<string> holiday(10);
unsigned int counter = 0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_timer = new QTimer(); // タイマーオブジェクトの作成

    // ボタンのクリックとスロットの結合
    connect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(showNext()));
    connect(ui->previousBtn, SIGNAL(clicked()), this, SLOT(showPrevious()));
    connect(ui->actionRead, SIGNAL(triggered()), this, SLOT(readFile()));
    connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(goodBy()));

    // タイマーシグナルtimeoutと処理用メソッドshow_timeの結合
//    connect(my_timer, SIGNAL(timeout()), this, SLOT(show_time()));
    //my_timer->start(100); // timerを開始する（1秒ごとに発火する）
}

MainWindow::~MainWindow()
{
    if (my_timer) delete my_timer; // newで作成したオブジェクトの破棄
    delete ui;
}

void MainWindow::show_time() {
//    update(); // paintEventが呼び出される
}

void MainWindow::showNext() {
    if (weekday.empty()) return;
    cout << "counter : " << counter << endl;
    cout << "weekday size : " << weekday.size() << endl;

    if (counter < weekday.size() - 1) {
        counter++;
    }

    ui->timeLabel->setText(QString::fromStdString(weekday[counter]));
}

void MainWindow::showPrevious() {
    cout << "counter : " << counter << endl;
    cout << "weekday size : " << weekday.size() << endl;

    if (weekday.empty()) return;
    if (counter > 0) {
        counter--;
    }

    ui->timeLabel->setText(QString::fromStdString(weekday[counter]));
}

void MainWindow::readFile() {
    // ファイル選択ダイアログより，hoge.jsonを選択する
    filePath = QFileDialog::getOpenFileName(this, tr("Select File"), ".", tr("JSON File (*.json)"));
    qDebug() << filePath; // "/Users/ken/QtProjects/Timer/timeSchedule.json"

    stringstream ss;
    ifstream f;

    // Read json file
    f.open(filePath.toUtf8().constData(), ios::binary);
    if (!f.is_open()) return;
    ss << f.rdbuf();
    f.close();

    value v;
    ss >> v;

    // エラーがあれば出力してreturn
    string err = get_last_error();
    if (!err.empty()) {
        cerr << err << endl;
        return;
    }

    object& o = v.get<object>()["TimeSchedule"].get<object>(); // TimeScheduleの括りを取得

    string from = o["From"].get<string>(); // Fromの部分を取得
    string to = o["To"].get<string>(); // Toの部分を取得

    array& a = o["Weekday"].get<array>();
    weekday.resize(a.size()); // vectorをリサイズ

    for (unsigned int i = 0; i < a.size(); i++) {
        cout << "i : " << i << endl;
        weekday[i] = a[i].get<string>();

        cout << "weekday : " << weekday[i] << endl;
    }

    cout << "From: " << from << endl; // Fromをコンソールに出力
    cout << "To: " << to << endl; // Toをコンソールに出力

    ui->timeLabel->setText(QString::fromStdString(to));
}

void MainWindow::goodBy() {
    exit(0); // プログラムの実行終了． exec()から抜け出す．
}
