#include <qdialog>
#include <qlineedit>
#include <qlabel>
#include <qgridlayout>
#include <qpushbutton>

class MinMax : public QDialog {
	Q_OBJECT
private:
	QLineEdit* max;
	QLineEdit* min;

public:
	MinMax(QWidget* parent = Q_NULLPTR);
	short Max() const { return max->text().toInt(); }
	short Min() const { return min->text().toInt(); }
};

