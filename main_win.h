#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

enum SQL_TYPE
{
    MS_SQL,MY_SQL,SQLITE
};

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Connect_clicked();
    void on_pushButton_Disconnect_clicked();
    void on_pushButton_Refresh_clicked();
    void on_comboBox_DBSelect_currentIndexChanged(int index);
    void on_toolButton_Path_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    QSqlError dbConnect();
    bool isSetting();
    void init();
    void setVisibleUI(bool visiable);
    void setEnableUI(bool enable);
    void errorMsg(QSqlError err);
    void tableWidgetShow(const QStringList &columnNames, const QHash<int, QList<QVariant> > &resultDatas);
};

#endif // MAINWINDOW_H
