#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "socialnetworkapp.h"

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
    // Slots to handle UI events
    void on_btnSetUser_clicked();
    void on_btnSetDate_clicked();
    void on_btnViewHome_clicked();
    void on_btnViewProfile_clicked();
    void on_btnViewFriendList_clicked();
    void on_btnViewLikedPages_clicked();
    void on_btnLikePost_clicked();
    void on_btnViewLikedList_clicked();
    void on_btnCommentPost_clicked();
    void on_btnViewPost_clicked();
    void on_btnShareMemory_clicked();
    void on_btnViewMemories_clicked();
    void on_btnViewPage_clicked();

    // Slot to update output text area
    void updateOutput(const QString& output);

    // Slot to update current user label
    void updateCurrentUser(const QString& userName);

private:
    Ui::MainWindow *ui;
    SocialNetworkApp *app; // Pointer to our app logic
};

#endif // MAINWINDOW_H
