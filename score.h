#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsItem>
#include <QString>

class Score {
    public:
        Score();
        QGraphicsTextItem *score_text;

        const int x = 10;
        const int y = 0;

        void add_score(int sc);

    private:
        int score_point;
        void set_text();

};

#endif // SCORE_H
