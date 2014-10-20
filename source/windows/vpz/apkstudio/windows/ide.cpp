#include "qdebug.h"
#include "ide.hpp"

using namespace VPZ::APKStudio::Components;
using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Windows {

IDE::IDE(QWidget *parent) :
    QMainWindow(parent), exit_code(0)
{
    Coder *coder = new Coder(this);
    highlighter = new Highlighter(this);
    highlighter->setDocument(coder->document());
    highlighter->setMode("xml");
    menu_bar = new MenuBar(this);
    status_bar = new QStatusBar(this);
    tool_bar = new ToolBar(this);
    setCentralWidget(coder);
    addToolBar(Qt::TopToolBarArea, tool_bar);
    setMenuBar(menu_bar);
    setStatusBar(status_bar);
}

void IDE::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes != QMessageBox::question(this, translate("mbox_close_title"), translate("mbox_close_message"), QMessageBox::No | QMessageBox::Yes))
        return;
    bool maximized = isMaximized();
    Settings::maximized(maximized);
    if (!maximized)
        Settings::windowSize(size());
    qApp->exit(exit_code);
}

void IDE::onActionContribute()
{
    QDesktopServices::openUrl(QUrl(URL_CONTRIBUTE));
}

void IDE::onActionDonate()
{
    QDesktopServices::openUrl(QUrl(URL_DONATE));
}

void IDE::onActionFeedbackIssues()
{
    QDesktopServices::openUrl(QUrl(URL_ISSUES));
}

void IDE::onActionFeedbackThanks()
{
    QDesktopServices::openUrl(QUrl(URL_THANKS));
}

void IDE::onActionQuit()
{
    exit_code = 0;
    close();
}

void IDE::onActionRestart()
{
    exit_code = EXIT_CODE_RESTART;
    close();
}

void IDE::onActionToggle(QAction *toggle)
{
    qDebug() << toggle->text();
}

void IDE::onInitComplete()
{
    // Resize
    setMinimumSize(QSize(800, 600));
    if (Settings::maximized())
        showMaximized();
    else
        resize(Settings::windowSize());
    // Window
    setDockOptions(AnimatedDocks | AllowNestedDocks);
    setWindowTitle(translate("window_title"));
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ