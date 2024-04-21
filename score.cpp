#include "score.h"

Score::Score() {
    score_point = 0;
    score_text = new QGraphicsTextItem;
    score_text->setDefaultTextColor(Qt::red);
    score_text->setScale(1.3);
    score_text->setPos(x, y);
    set_text();
}

void Score::add_score(int sc = 1) {
    score_point += sc;
    set_text();
}

void Score::reset_score() {
    score_point = 0;
    set_text();
}

void Score::set_text() {
    QString score_text_combined = "Score: " + QString::number(score_point);
    score_text->setPlainText(score_text_combined);
}

