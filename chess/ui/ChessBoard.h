#pragma once

#include <QPainter>
#include <QSvgWidget>
#include <QPainterPath>
#include <QResizeEvent>
#include <QWidget>
#include <QPropertyAnimation>
#include <QtWidgets/QGridLayout>

#include "../core/Piece.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    /*
     * 行进方阵营标记
     * */
    class CampHint final : public QWidget {
    Q_OBJECT
    public:
        QPropertyAnimation* animation;

        QWidget* hint;

    public:
        CampHint() {
            hint = new QWidget(this);
            hint->setGeometry(QRect(0, height(), 3, 200));
            hint->setObjectName("Hint");

            animation = new QPropertyAnimation;
            animation->setPropertyName(QByteArray("geometry"));
            animation->setDuration(400);
            animation->setTargetObject(hint);
        }

        void reverse(const bool flag) const {
            if (flag)
            {
                animation->setStartValue(QRect(0, height() / 2 - 200, 3, 200));
                animation->setEndValue(QRect(0, height() / 2, 3, 200));
                animation->start();
            }
            else
            {
                animation->setStartValue(QRect(0, height() / 2, 3, 200));
                animation->setEndValue(QRect(0, height() / 2 - 200, 3, 200));
                animation->start();
            }
        }
    };

    /*
     * 棋子控件，加载棋子图片
     * */
    class PieceWidget final : public QSvgWidget {
    Q_OBJECT
    public:
        std::shared_ptr<Piece> logicPiece;

    public:
        explicit PieceWidget(std::shared_ptr<Piece>& piece) : logicPiece(piece) {
        }

    signals:

        void getPos(int);

    protected:
        [[maybe_unused]] void mousePressEvent(QMouseEvent*) override {
            emit getPos(logicPiece->pos_);
        }
    };

    /*
     * 棋盘控件，加载棋盘图片
     * */
    class ChessBoardQWidget final : public QSvgWidget {
    Q_OBJECT
    public:
        ChessBoardQWidget() { load(QString(":/board.svg")); }
    };

    /*
     * 棋盘主控件，重写resizeEvent，使子控件->棋盘控件保持比例
     * */
    class ChessBoard final : public QWidget {
    Q_OBJECT
    private:
        int widthRatio;
        int heightRatio;

    public:
        QBoxLayout* layout;
        ChessBoardQWidget* board;
        QGridLayout* boardLayout;

    public:
        ChessBoard() : widthRatio(9), heightRatio(10) {
            layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(0);
            this->setLayout(layout);
            board = new ChessBoardQWidget;

            layout->addWidget(board);
            boardLayout = new QGridLayout;
            boardLayout->setContentsMargins(0, 0, 0, 0);
            boardLayout->setSpacing(2);
            board->setLayout(boardLayout);
            for (int i = 0; i < 9; ++i)
            {
                boardLayout->setColumnStretch(i, 1);
                boardLayout->setRowStretch(i, 1);
            }
            boardLayout->setRowStretch(9, 1);
        }

        void resizeEvent(QResizeEvent* event) override {
            const QSize oldSize = event->size();
            QSize newSize = event->size();

            if (newSize.width() < widthRatio * newSize.height() / heightRatio)
            {
                newSize.setHeight(heightRatio * newSize.width() / widthRatio);
                board->move(0, (oldSize.height() - newSize.height()) / 2);
            }
            else
            {
                newSize.setWidth(widthRatio * newSize.height() / heightRatio);
                board->move((oldSize.width() - newSize.width()) / 2, 0);
            }
            board->resize(newSize);
        }
    };
}

QT_END_NAMESPACE
