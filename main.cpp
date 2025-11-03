// main.cpp  (Jiahao's GUI + Omar's Top/Bottom + Merge Sort)
#include "functions.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QTimer>

using namespace std;
static CoffeeManager gManager;

class MainMenuWindow;
class StartWindow;

class MainMenuWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
};

class StartWindow : public QWidget {
    Q_OBJECT
    QProgressBar *bar = nullptr;
    QTimer *timer = nullptr;
    int progress = 0;
public:
    explicit StartWindow(QWidget *parent = nullptr);
private slots:
    void startGeneration();
    void updateProgress();
};

MainMenuWindow::MainMenuWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Main Menu");
    resize(400, 400);
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40,40,40,40);
    layout->addWidget(new QLabel("<h2>Main Menu</h2>", this), 0, Qt::AlignCenter);

    QStringList opts = {
        "1. Compute quality scores",
        "2. Display top N coffees",
        "3. Display bottom N coffees"
    };

    for (const auto& opt : opts) {
        auto *btn = new QPushButton(opt, this);
        layout->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, [this, opt]() {
            if (opt.contains("top")) {
                auto top10 = gManager.getTopN(10);
                if (top10.empty()) {
                    QMessageBox::warning(this, "Error", "No coffee data generated yet!");
                    return;
                }
                QString msg;
                for (int i = 0; i < top10.size(); i++) {
                    msg += QString::number(i + 1) + ". "
                         + QString::fromStdString(top10[i].owner)
                         + " (" + QString::number(top10[i].total, 'f', 2) + ")\n";
                }
                QMessageBox::information(this, "Top 10 Coffees", msg);
            }
            else if (opt.contains("bottom")) {
                auto bottom10 = gManager.getBottomN(10);
                if (bottom10.empty()) {
                    QMessageBox::warning(this, "Error", "No coffee data generated yet!");
                    return;
                }
                QString msg;
                for (int i = 0; i < bottom10.size(); i++) {
                    msg += QString::number(i + 1) + ". "
                         + QString::fromStdString(bottom10[i].owner)
                         + " (" + QString::number(bottom10[i].total, 'f', 2) + ")\n";
                }
                QMessageBox::information(this, "Bottom 10 Coffees", msg);
            }
            else if (opt.contains("Compute")) {
                QMessageBox::information(this, "Info",
                                         "Quality score calculation feature (Anna’s part) coming soon!");
            }
        });
    }
}

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Coffee Data Generator");
    resize(400, 300);

    auto *layout = new QVBoxLayout(this);
    layout->addStretch();

    auto *btn = new QPushButton("Generate data", this);
    btn->setStyleSheet("font-size: 18px; padding: 15px;");
    layout->addWidget(btn, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(btn, &QPushButton::clicked, this, &StartWindow::startGeneration);
}

void StartWindow::startGeneration() {
    bool click;
    int n = QInputDialog::getInt(this, "Input", "Records (>=100000):",
                                 100000, 100000, 10000000, 1, &click);
    if (!click) return; //user cancelled


    QLayoutItem *item;
    while ((item = layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    auto* mainLayout = qobject_cast<QVBoxLayout*>(layout());
    if (!mainLayout) {
        mainLayout = new QVBoxLayout(this);
        setLayout(mainLayout);
    }

    mainLayout->addStretch();
    mainLayout->addWidget(new QLabel("Generating coffee data...", this), 0, Qt::AlignCenter);

    bar = new QProgressBar(this);
    bar->setRange(0, 100);
    mainLayout->addWidget(bar);
    mainLayout->addStretch();

    // progress animation
    progress = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartWindow::updateProgress);
    timer->start(30);

    //real generation (runs after a short visual delay)
    QTimer::singleShot(300, this, [this, n]() {
        gManager.generate(n);
        timer->stop();
        bar->setValue(100);
        QTimer::singleShot(400, this, [this]() {
            close();
            (new MainMenuWindow())->show();
        });
    });
}

void StartWindow::updateProgress() {
    progress = qMin(progress + 1, 100);
    bar->setValue(progress);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    (new StartWindow())->show();
    return app.exec();
}

#include "main.moc"
