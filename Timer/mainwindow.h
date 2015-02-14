#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT // Qtのクラスを宣言する時に置くマクロ

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    class QTimer *my_timer; // 描画画面更新用タイマー．タイマーイベントを発生させる

public slots:
    void show_time(); // タイマーイベント処理用メソッド
    void goodBy(); // ボタンクリック処理用メソッド
    void showNext();
    void showPrevious();
    void readFile(); // File→Readを選択した際のメソッド
};

#endif // MAINWINDOW_H
