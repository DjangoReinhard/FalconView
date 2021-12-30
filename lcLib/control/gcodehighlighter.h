#ifndef GCODEHIGHLIGHTER_H
#define GCODEHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QVector>


class GCodeHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT
public:
  GCodeHighlighter(QTextDocument* parent);
  GCodeHighlighter(QObject* parent = nullptr);
  GCodeHighlighter(const GCodeHighlighter& other);

  void highlightBlock(const QString &text) override;

protected:
  void setup();

private:
  struct HighlightingRule
  {
    QRegularExpression pattern;
    QTextCharFormat format;
    };
  QVector<HighlightingRule> highlightingRules;

  QTextCharFormat fmtNumber;
  QTextCharFormat fmtGCode;
  QTextCharFormat fmtMotion;
  QTextCharFormat fmtMCode;
  QTextCharFormat fmtPos;
  QTextCharFormat fmtXPos;
  QTextCharFormat fmtTool;
  QTextCharFormat fmtFeed;
  QTextCharFormat fmtSpeed;
  QTextCharFormat fmtVar;
  QTextCharFormat fmtComment;
  QTextCharFormat fmtLineComment;
  };
#endif // GCODEHIGHLIGHTER_H
