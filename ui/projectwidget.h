#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QPushButton>
#include <QAudioOutput>
#include "../backend/project.h"
#include "projectinsertion.h"
#include "projectrollback.h"

namespace Ui {
class ProjectWidget;
}

class ProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectWidget(QWidget *parent = nullptr);
    ~ProjectWidget();

private slots:
    // List tab slots
    void onRefreshProjectsClicked();
    
    // Add tab slots
    void onAddProjectClicked();
    void onUpdateProjectClicked(qint64 projectId);
    
    // Table button slots
    void onEditFromTableClicked();
    void onDeleteFromTableClicked();
    // Search, sort and export
    void onSearchProject(const QString &keyword);
    void onSearchProjectClicked();
    void onSortByTitleClicked();
    void onExportExelClicked();
    void onStatisticsClicked();

    // Insertion (media) slots
    void onInsertionImportClicked();
    void onInsertionRemoveClicked();
    void onInsertionClearClicked();
    // removed onInsertionOpenClicked - 'open in default player' was removed
    void onInsertionItemActivated(QListWidgetItem* item);
    void onPlayPauseClicked();
    void onVideoPositionChanged(qint64 position);
    void onVideoDurationChanged(qint64 duration);
    void onVideoSliderMoved(int value);

    // Rollback slots
    void onRollbackAddClicked();
    void onRollbackDoClicked();
    void onRollbackClearClicked();

private:
    Ui::ProjectWidget *ui;
    bool isEditingMode = false;
    qint64 currentEditingProjectId = -1;
    
    // Helper methods
    void loadAllProjects();
    void populateProjectTable(const QVector<Project> &projects);
    void clearAddForm();
    void refreshTable();

    // Insertion & Rollback handlers
    ProjectInsertion *insertionHandler;
    ProjectRollback *rollbackHandler;

    // Insertion & Rollback helpers
    void loadMediaListUI();
    void loadRollbackHistoryUI();
    void showMediaPreview(const QString &path);

    // Video player helpers
    void setupVideoPlayer();

    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QSlider *videoSlider;
    QPushButton *playPauseBtn;
    QAudioOutput *audioOutput;

};

#endif // PROJECTWIDGET_H
