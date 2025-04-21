// Copyright (c) 2023-2025 Manuel Schneider

#pragma once
#include <QCoreApplication>
#include <albert/item.h>
#include <albert/query.h>
#include <set>

class VpnConnectionItem : public albert::Item
{
    Q_DECLARE_TR_FUNCTIONS(VpnConnectionItem)

public:

    enum class State {
        Invalid,
        Disconnected,
        Connecting,
        Connected,
        Disconnecting
    };

    static QString stateString(State state);

    QString subtext() const override;
    QStringList iconUrls() const override;
    QString inputActionText() const override;
    void addObserver(albert::Item::Observer*) override;
    void removeObserver(albert::Item::Observer*) override;

    State state() const;
    void setState(State state);

private:

    State state_;
    std::set<albert::Item::Observer*> observers;
};
