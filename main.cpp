// main.cpp — The Ethnic Tree Project
// Team: Omar Elsayed, Anna Grace Haukoos, Jiahao Liu
// Comparing Merge Sort and Quick Sort for Coffee Quality Sorting
// main.cpp — The Ethnic Tree Project
// Team: Omar Elsayed, Anna Grace Haukoos, Jiahao Liu
// Comparing Merge Sort and Quick Sort for Coffee Quality Sorting
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
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QPixmap>
#include <QPalette>
#include <QDir>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <QTableWidget>
#include <QDialog>
#include <QHeaderView>
#include <QScrollBar>
using namespace std;

static CoffeeManager gManager;

class MainMenuWindow;
class StartWindow;

class MainMenuWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent* event) override;
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
protected:
    void resizeEvent(QResizeEvent* event) override;
};

MainMenuWindow::MainMenuWindow(QWidget *parent) : QWidget(parent){
    setWindowTitle("Coffee Quality Sorter");
    resize(500, 500);

    QPixmap bg(":/icons/bean.jpg");
    if (!bg.isNull()){
        QPalette palette;
        palette.setBrush(QPalette::Window, bg.scaled(size(), Qt::KeepAspectRatioByExpanding));
        setAutoFillBackground(true);
        setPalette(palette);
    }

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40,40,40,40);

    QLabel *title = new QLabel("<h2>Coffee Quality Sorter</h2>", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "color: #3e2c27;"
        "font-weight: 900;"
        "font-size: 34px;"
        "letter-spacing: 1px;"
        "text-shadow: 2px 2px 6px #b68f60;"
    );
    QLabel *subtitle = new QLabel("<i>Compare Merge Sort and Quick Sort on coffee data</i>", this);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet(
        "color: #3e2c27;"
        "font-size: 17px;"
        "font-weight: 600;"
        "font-style: italic;"
        "text-shadow: 1px 1px 3px #2e1e14;"
        "margin-bottom: 15px;"
    );

    layout->addWidget(title, 0, Qt::AlignCenter);
    layout->addWidget(subtitle, 0, Qt::AlignCenter);
    layout->addStretch();

    QStringList opts = {
        "1. Compute Quality Scores",
        "2. Display Top 10 Coffees",
        "3. Display Bottom 10 Coffees",
        "4. Sort Using Merge Sort",
        "5. Sort Using Quick Sort",
        "6. Compare Merge vs Quick Sort",
        "7. Display All Data"
    };

    for (const auto& opt : opts){
        auto *btn = new QPushButton(opt, this);
        btn->setStyleSheet(
            "font-weight:bold;"
            "font-size:15px;"
            "color:#f8e5c0;"
            "background-color:#3e2c27;"
            "border-radius:8px;"
            "padding:10px;"
            "border:1px solid #8b5a2b;"
            "transition:all 0.2s;"
        );
        btn->setCursor(Qt::PointingHandCursor);

        connect(btn, &QPushButton::pressed, [btn](){
            btn->setStyleSheet(
                "font-weight:bold;"
                "font-size:15px;"
                "color:white;"
                "background-color:#5a3a2b;"
                "border-radius:8px;"
                "padding:10px;"
                "border:1px solid #a9744f;"
            );
        });
        connect(btn, &QPushButton::released, [btn](){
            btn->setStyleSheet(
                "font-weight:bold;"
                "font-size:15px;"
                "color:#f8e5c0;"
                "background-color:#3e2c27;"
                "border-radius:8px;"
                "padding:10px;"
                "border:1px solid #8b5a2b;"
            );
        });

        layout->addWidget(btn);

        connect(btn, &QPushButton::clicked, this, [this, opt](){
            if (opt.contains("Top")){
                auto top10 = gManager.getTopN(10);
                if (top10.empty()){
                    QMessageBox::warning(this, "Error", "No coffee data generated yet!");
                    return;
                }
                QDialog *dlg = new QDialog(this);
                dlg->setWindowTitle("Top 10 Coffees");
                QVBoxLayout *lay = new QVBoxLayout(dlg);
                QTableWidget *table = new QTableWidget(dlg);
                table->setRowCount(top10.size());
                table->setColumnCount(3);
                table->setHorizontalHeaderLabels({"Rank", "Owner", "Score"});
                for (int i = 0; i < top10.size(); i++){
                    table->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
                    table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(top10[i].owner)));
                    table->setItem(i, 2, new QTableWidgetItem(QString::number(top10[i].total, 'f', 2)));
                }
                table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                lay->addWidget(table);
                dlg->resize(400, 300);
                dlg->exec();
            }

            else if (opt.contains("Bottom")){
                auto bottom10 = gManager.getBottomN(10);
                if (bottom10.empty()){
                    QMessageBox::warning(this, "Error", "No coffee data generated yet!");
                    return;
                }
                QDialog *dlg = new QDialog(this);
                dlg->setWindowTitle("Bottom 10 Coffees");
                QVBoxLayout *lay = new QVBoxLayout(dlg);
                QTableWidget *table = new QTableWidget(dlg);
                table->setRowCount(bottom10.size());
                table->setColumnCount(3);
                table->setHorizontalHeaderLabels({"Rank", "Owner", "Score"});
                for (int i = 0; i < bottom10.size(); i++){
                    table->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
                    table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(bottom10[i].owner)));
                    table->setItem(i, 2, new QTableWidgetItem(QString::number(bottom10[i].total, 'f', 2)));
                }
                table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                lay->addWidget(table);
                dlg->resize(400, 300);
                dlg->exec();
            }

            else if (opt.contains("Compute")){
                if (gManager.getData().empty()){
                    QMessageBox::warning(this, "Error", "No data generated yet!");
                    return;
                }
                std::vector<Coffee> copy = gManager.getData();
                CoffeeManager localManager;
                std::string finalResult = localManager.calculateQualityScore(copy);
                QString overallResult = QString::fromStdString(finalResult);
                QMessageBox::information(this, "Final Quality Score", overallResult);
            }
            else if (opt.contains("Compare")){
                if (gManager.getData().empty()){
                    QMessageBox::warning(this, "Error", "No data generated yet!");
                    return;
                }
                std::vector<Coffee> copy1 = gManager.getData();
                std::vector<Coffee> copy2 = gManager.getData();
                CoffeeManager localManager;

                auto start1 = std::chrono::high_resolution_clock::now();
                localManager.mergeSort(copy1, 0, copy1.size() - 1);
                auto end1 = std::chrono::high_resolution_clock::now();
                double mergeMs = std::chrono::duration<double, std::milli>(end1 - start1).count();

                auto start2 = std::chrono::high_resolution_clock::now();
                localManager.quickSort(copy2, 0, copy2.size() - 1);
                auto end2 = std::chrono::high_resolution_clock::now();
                double quickMs = std::chrono::duration<double, std::milli>(end2 - start2).count();

                std::stringstream ss;
                ss << "Merge Sort: " << std::fixed << std::setprecision(2)
                   << mergeMs << " ms\n"
                   << "Quick Sort: " << quickMs << " ms\n\n";
                ss << "Fastest: " << ((mergeMs < quickMs) ? "Merge Sort" : "Quick Sort") << "\n\n";
                ss << "Top Coffee (Merge): " << copy1[0].owner << " (" << copy1[0].total << ")\n";
                ss << "Top Coffee (Quick): " << copy2[0].owner << " (" << copy2[0].total << ")";
                QMessageBox::information(this, "Sort Comparison Results",
                                         QString::fromStdString(ss.str()));
            }
            else if (opt.contains("Merge")){
                if (gManager.getData().empty()){
                    QMessageBox::warning(this, "Error", "No data generated yet!");
                    return;
                }
                std::vector<Coffee> copy = gManager.getData();
                CoffeeManager localManager;

                auto start = std::chrono::high_resolution_clock::now();
                localManager.mergeSort(copy, 0, copy.size() - 1);
                auto end = std::chrono::high_resolution_clock::now();
                double ms = std::chrono::duration<double, std::milli>(end - start).count();

                std::stringstream ss;
                ss << "Merge Sort completed in " << std::fixed << std::setprecision(2)
                   << ms << " ms.\n\nTop coffee:\n"
                   << copy[0].country << " - " << copy[0].region << " - "
                   << copy[0].owner << " (" << copy[0].total << ")";
                QMessageBox::information(this, "Merge Sort Result",
                                         QString::fromStdString(ss.str()));
            }

            else if (opt.contains("Quick")){
                if (gManager.getData().empty()){
                    QMessageBox::warning(this, "Error", "No data generated yet!");
                    return;
                }
                std::vector<Coffee> copy = gManager.getData();
                CoffeeManager localManager;

                auto start = std::chrono::high_resolution_clock::now();
                localManager.quickSort(copy, 0, copy.size() - 1);
                auto end = std::chrono::high_resolution_clock::now();
                double ms = std::chrono::duration<double, std::milli>(end - start).count();

                std::stringstream ss;
                ss << "Quick Sort completed in " << std::fixed << std::setprecision(2)
                   << ms << " ms.\n\nTop coffee:\n"
                   << copy[0].country << " - " << copy[0].region << " - "
                   << copy[0].owner << " (" << copy[0].total << ")";
                QMessageBox::information(this, "Quick Sort Result",
                                         QString::fromStdString(ss.str()));
            }
            else if (opt.contains("All Data")){
                if (gManager.getData().empty()){
                    QMessageBox::warning(this, "Error", "No data generated yet!");
                    return;
                }
                const auto& data = gManager.getData();
                QDialog *dlg = new QDialog(this);
                dlg->setWindowTitle("All Coffee Data");
                QVBoxLayout *lay = new QVBoxLayout(dlg);
                QTableWidget *table = new QTableWidget(dlg);
                table->setRowCount(data.size());
                table->setColumnCount(13);
                table->setHorizontalHeaderLabels({
                    "Country", "Region", "Owner", "Aroma", "Flavor", "Aftertaste",
                    "Acidity", "Body", "Balance", "Uniformity", "Sweet", "Moisture", "Total"
                });
                for (size_t row = 0; row < data.size(); ++row) {
                    const Coffee& c = data[row];
                    table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(c.country)));
                    table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(c.region)));
                    table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(c.owner)));
                    table->setItem(row, 3, new QTableWidgetItem(QString::number(c.aroma, 'f', 2)));
                    table->setItem(row, 4, new QTableWidgetItem(QString::number(c.flavor, 'f', 2)));
                    table->setItem(row, 5, new QTableWidgetItem(QString::number(c.aftertaste, 'f', 2)));
                    table->setItem(row, 6, new QTableWidgetItem(QString::number(c.acidity, 'f', 2)));
                    table->setItem(row, 7, new QTableWidgetItem(QString::number(c.body, 'f', 2)));
                    table->setItem(row, 8, new QTableWidgetItem(QString::number(c.balance, 'f', 2)));
                    table->setItem(row, 9, new QTableWidgetItem(QString::number(c.uniformity, 'f', 2)));
                    table->setItem(row, 10, new QTableWidgetItem(QString::number(c.sweet, 'f', 2)));
                    table->setItem(row, 11, new QTableWidgetItem(QString::number(c.moisture, 'f', 2)));
                    table->setItem(row, 12, new QTableWidgetItem(QString::number(c.total, 'f', 2)));
                }
                table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                lay->addWidget(table);
                dlg->resize(1200, 800);
                dlg->exec();
            }
        });
    }
}

void MainMenuWindow::resizeEvent(QResizeEvent* event){
    QPixmap bg(":/icons/bean.jpg");
    if (!bg.isNull()){
        QPalette palette;
        palette.setBrush(QPalette::Window, bg.scaled(size(), Qt::KeepAspectRatioByExpanding));
        setPalette(palette);
    }
    QWidget::resizeEvent(event);
}

StartWindow::StartWindow(QWidget *parent) : QWidget(parent){
    setWindowTitle("Coffee Data Generator");
    resize(400,300);

    QPixmap bg(":/icons/bean.jpg");
    if (!bg.isNull()){
        QPalette palette;
        palette.setBrush(QPalette::Window, bg.scaled(size(), Qt::KeepAspectRatioByExpanding));
        setAutoFillBackground(true);
        setPalette(palette);
    }

    auto *layout = new QVBoxLayout(this);
    layout->addStretch();
    auto *btn = new QPushButton("Generate data", this);
    btn->setStyleSheet("font-size:18px; padding:15px; background-color:#3e2c27; color:#f8e5c0; border-radius:8px; border:1px solid #8b5a2b;");
    layout->addWidget(btn, 0, Qt::AlignCenter);
    layout->addStretch();
    connect(btn, &QPushButton::clicked, this, &StartWindow::startGeneration);
}
void StartWindow::startGeneration(){
    bool click;
    int n = QInputDialog::getInt(this, "Input", "Records (>=100000):",
                                 100000, 100000, 10000000, 1, &click);
    if (!click) return;
    QLayoutItem *item;
    while ((item = layout()->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }
    auto* mainLayout = qobject_cast<QVBoxLayout*>(layout());
    if (!mainLayout){
        mainLayout = new QVBoxLayout(this);
        setLayout(mainLayout);
    }
    mainLayout->addStretch();
    mainLayout->addWidget(new QLabel("Generating coffee data...", this), 0, Qt::AlignCenter);
    bar = new QProgressBar(this);
    bar->setRange(0, 100);
    mainLayout->addWidget(bar);
    mainLayout->addStretch();
    progress = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartWindow::updateProgress);
    timer->start(30);
    QTimer::singleShot(300, this, [this, n](){
        gManager.generate(n);
        timer->stop();
        bar->setValue(100);
        QTimer::singleShot(400, this, [this](){
            close();
            (new MainMenuWindow())->show();
        });
    });
}
void StartWindow::updateProgress(){
    progress = qMin(progress + 1, 100);
    bar->setValue(progress);
}

void StartWindow::resizeEvent(QResizeEvent* event){
    QPixmap bg(":/icons/bean.jpg");
    if (!bg.isNull()){
        QPalette palette;
        palette.setBrush(QPalette::Window, bg.scaled(size(), Qt::KeepAspectRatioByExpanding));
        setPalette(palette);
    }
    QWidget::resizeEvent(event);
}

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    StartWindow* window = new StartWindow();
    window->show();
    return app.exec();
}

#include "main.moc"