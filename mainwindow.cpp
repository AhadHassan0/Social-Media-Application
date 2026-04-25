#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create SocialNetworkApp instance
    app = new SocialNetworkApp(this);

    // Connect signals from app to slots in this class
    connect(app, &SocialNetworkApp::outputGenerated, this, &MainWindow::updateOutput);
    connect(app, &SocialNetworkApp::currentUserChanged, this, &MainWindow::updateCurrentUser);

    // Initialize the application
    app->Run();

    // Update UI with initial message
    updateOutput("Welcome to Social Network Application!");
}

MainWindow::~MainWindow()
{
    delete ui;
    // app is a child QObject, so it will be deleted automatically
}

// Updates the output text area with new text
void MainWindow::updateOutput(const QString& output)
{
    ui->txtOutput->setPlainText(output);
}

// Updates the current user label
void MainWindow::updateCurrentUser(const QString& userName)
{
    ui->lblCurrentUser->setText("Current User: " + userName);
}

// Sets the current user
void MainWindow::on_btnSetUser_clicked()
{
    QString userID = ui->txtUserID->text();
    if (userID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a user ID!");
        return;
    }

    app->onSetCurrentUserClicked(userID);
}

// Sets the current date
void MainWindow::on_btnSetDate_clicked()
{
    int day = ui->spinDay->value();
    int month = ui->spinMonth->value();
    int year = ui->spinYear->value();

    app->onSetCurrentDateClicked(day, month, year);
}

// Views home page
void MainWindow::on_btnViewHome_clicked()
{
    app->onViewHomeClicked();
}

// Views profile
void MainWindow::on_btnViewProfile_clicked()
{
    app->onViewProfileClicked();
}

// Views friend list
void MainWindow::on_btnViewFriendList_clicked()
{
    app->onViewFriendListClicked();
}

// Views liked pages
void MainWindow::on_btnViewLikedPages_clicked()
{
    app->onViewLikedPagesClicked();
}
// Likes a post
void MainWindow::on_btnLikePost_clicked()
{
    QString postID = ui->txtPostID->text();
    if (postID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a post ID!");
        return;
    }

    app->onLikePostClicked(postID);
}

// Views users who liked a post
void MainWindow::on_btnViewLikedList_clicked()
{
    QString postID = ui->txtPostID->text();
    if (postID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a post ID!");
        return;
    }

    app->onViewLikedListClicked(postID);
}

// Comments on a post
void MainWindow::on_btnCommentPost_clicked()
{
    QString postID = ui->txtPostID->text();
    QString comment = ui->txtComment->text();

    if (postID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a post ID!");
        return;
    }

    if (comment.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a comment!");
        return;
    }

    app->onCommentOnPostClicked(postID, comment);
}

// Views a post
void MainWindow::on_btnViewPost_clicked()
{
    QString postID = ui->txtPostID->text();
    if (postID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a post ID!");
        return;
    }

    app->onViewPostClicked(postID);
}

// Shares a memory
void MainWindow::on_btnShareMemory_clicked()
{
    QString postID = ui->txtPostID->text();
    QString text = ui->txtMemoryText->text();

    if (postID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a post ID!");
        return;
    }

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter memory text!");
        return;
    }

    app->onShareMemoryClicked(postID, text);
}

// Sees memories
void MainWindow::on_btnViewMemories_clicked()
{
    app->onSeeYourMemoriesClicked();
}

// Views a page
void MainWindow::on_btnViewPage_clicked()
{
    QString pageID = ui->txtPageID->text();
    if (pageID.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a page ID!");
        return;
    }

    app->onViewPageClicked(pageID);
}
