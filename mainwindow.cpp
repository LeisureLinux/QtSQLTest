#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    //db close & removedatabase
    if(db.isOpen())
    {
        db.close();
    }
    QSqlDatabase::removeDatabase(db.connectionName());
    delete ui;
}

void MainWindow::on_pushButton_Connect_clicked()
{
    if(!isSetting())
    {
        QMessageBox::critical(this,"SqlTest","Edit is empty.");
        return;
    }

    QSqlError err=dbConnect();
    if(err.type()!=QSqlError::NoError)
    {
        errorMsg(err);
        return;
    }
    setEnableUI(false);
}

void MainWindow::on_pushButton_Disconnect_clicked()
{
    if(db.isOpen())
    {
        db.close();
    }
    db=QSqlDatabase();
    QSqlDatabase::removeDatabase("MainDB");
    setEnableUI(true);
}

void MainWindow::on_pushButton_Refresh_clicked() //db query exec (select command)
{
    if(ui->lineEdit_Command->text().isEmpty())
    {
        QMessageBox::warning(this,"SqlTest","请输入SQL命令，以分号结束");
        return;
    }
    if(!db.isOpen())
    {
        QSqlError err=dbConnect();
        if(err.type()!=QSqlError::NoError)
        {
           errorMsg(err);
           return;
        }
    }

    QSqlQuery query(db);
    QList<QVariant> rowResultDatas;
    QHash<int,QList<QVariant>> resultDatas;
    QStringList columnNames;
    int queryCount=0;

    query.setForwardOnly(true);
    query.prepare(ui->lineEdit_Command->text());
    query.exec();

    if(query.lastError().type()!=QSqlError::NoError)
    {
        errorMsg(query.lastError());
        return;
    }

    for(int i=0; i<query.record().count(); i++)
    {
        columnNames.append(query.record().fieldName(i));
    }

    while(query.next())
    {
        for(int i=0; i<query.record().count(); i++)
        {
            rowResultDatas.append(query.value(i));
        }

        resultDatas.insert(queryCount++,rowResultDatas);
        rowResultDatas.clear();
    }
    query.finish();

    if(!resultDatas.isEmpty())
    {
        tableWidgetShow(columnNames,resultDatas);
    }
}

QSqlError MainWindow::dbConnect() //connect db
{
    switch (ui->comboBox_DBSelect->currentIndex()) {
    case MS_SQL:
        db=QSqlDatabase::addDatabase("QODBC","MainDB");
        db.setDatabaseName(QString("Driver={SQL Server};Server=%1,%2;Database=%3;Uid=%4;Pwd=%5;")
                           .arg(ui->lineEdit_Server->text(),ui->lineEdit_Port->text(),ui->lineEdit_DBName->text())
                           .arg(ui->lineEdit_UserName->text(),ui->lineEdit_Password->text()));
        break;
    case MY_SQL:
        db=QSqlDatabase::addDatabase("QMYSQL","MainDB");
        db.setHostName(ui->lineEdit_Server->text());
        db.setDatabaseName(ui->lineEdit_DBName->text());
        db.setPort(ui->lineEdit_Port->text().toInt());
        db.setUserName(ui->lineEdit_UserName->text());
        db.setPassword(ui->lineEdit_Password->text());
        break;
    case SQLITE:
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(ui->lineEdit_DBName->text());
        break;
    default:        
        break;
    }

    if(!db.open()){ return db.lastError();}
    return QSqlError();
}

bool MainWindow::isSetting() //setting check
{
    switch (ui->comboBox_DBSelect->currentIndex()) {
    case MS_SQL: case MY_SQL:
        if(ui->lineEdit_DBName->text().isEmpty() || ui->lineEdit_Password->text().isEmpty() ||ui->lineEdit_Port->text().isEmpty()
                || ui->lineEdit_Server->text().isEmpty() || ui->lineEdit_UserName->text().isEmpty())
        {
            return false;
        }
        break;
    case SQLITE:
        if(ui->lineEdit_DBName->text().isEmpty())
        {
            return false;
        }
        break;
    default:
        break;
    }

    return true;
}

void MainWindow::init()
{
    ui->comboBox_DBSelect->addItems(QStringList()<<"MSSQL"<<"MYSQL"<<"SQLITE");
    ui->comboBox_DBSelect->setCurrentIndex(0);
}

void MainWindow::setVisibleUI(bool visiable)
{
    ui->toolButton_Path->setVisible(!visiable);
    ui->label_Password->setVisible(visiable);
    ui->label_Port->setVisible(visiable);
    ui->label_Server->setVisible(visiable);
    ui->label_UserName->setVisible(visiable);
    ui->lineEdit_Password->setVisible(visiable);
    ui->lineEdit_Port->setVisible(visiable);
    ui->lineEdit_Server->setVisible(visiable);
    ui->lineEdit_UserName->setVisible(visiable);
}

void MainWindow::setEnableUI(bool enable)
{
    ui->pushButton_Connect->setEnabled(enable);
    ui->pushButton_Disconnect->setEnabled(!enable);
    ui->pushButton_Refresh->setEnabled(!enable);
    ui->comboBox_DBSelect->setEnabled(enable);
    ui->toolButton_Path->setEnabled(enable);
    ui->lineEdit_DBName->setEnabled(enable);
    ui->lineEdit_Password->setEnabled(enable);
    ui->lineEdit_Port->setEnabled(enable);
    ui->lineEdit_Server->setEnabled(enable);
    ui->lineEdit_UserName->setEnabled(enable);
}

void MainWindow::errorMsg(QSqlError err) //exception db
{
    db.close();
    QSqlDatabase::removeDatabase("MainDB");
    db=QSqlDatabase();
    QMessageBox::critical(this,"SqlTest",err.text());    
    setEnableUI(true);
}

void MainWindow::tableWidgetShow(const QStringList &columnNames, const QHash<int, QList<QVariant>> &resultDatas) //data table
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(columnNames.count());
    ui->tableWidget->setHorizontalHeaderLabels(columnNames);
    ui->tableWidget->setRowCount(resultDatas.keys().count());

    QProgressDialog progressDlg(this);
    progressDlg.setLabelText(tr("Data reading..."));
    progressDlg.setRange(0,resultDatas.keys().count());
    progressDlg.setValue(0);
    progressDlg.setModal(true);
    progressDlg.setMinimumDuration(100);
    progressDlg.show();

    QList<QVariant> datas;

    for(int i=0; i<resultDatas.keys().count(); i++)
    {
        datas=resultDatas[i];
        for(int j=0; j<datas.count(); j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(datas.at(j).toString()));
        }
        progressDlg.setValue(i);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_comboBox_DBSelect_currentIndexChanged(int index) //selected combo
{
    switch (index) {
    case MS_SQL:
        ui->lineEdit_Port->setText("1433");
        setVisibleUI(true);
        break;
    case MY_SQL:
        ui->lineEdit_Port->setText("3306");
        setVisibleUI(true);
        break;
    case SQLITE:
        setVisibleUI(false);
        break;
    default:
        break;
    }
}

void MainWindow::on_toolButton_Path_clicked(bool checked) //sqlite file open
{
    QString fileName=QFileDialog::getOpenFileName(this,"Open file",QApplication::applicationDirPath(),"SQLite (*.db *.sqlite *.sqlite3 *.db3)");

    if(fileName.isEmpty())
    {
        return;
    }

    ui->lineEdit_DBName->setText(fileName);
}
