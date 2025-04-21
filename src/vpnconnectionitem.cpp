// Copyright (c) 2023-2025 Manuel Schneider

#include "vpnconnectionitem.h"
#include <albert/logging.h>


QString VpnConnectionItem::stateString(State state)
{
    switch (state) {
    case State::Invalid: return tr("Invalid");
    case State::Disconnected: return tr("Disconnected");
    case State::Connecting: return tr("Connecting…");
    case State::Connected: return tr("Connected");
    case State::Disconnecting: return tr("Disconnecting…");
    default: qFatal("VpnConnectionItem::stateString: Invalid state %d", (int)state);
    }
}

QString VpnConnectionItem::subtext() const
{
    return tr("VPN connection: %1").arg(stateString(state_));
}

QStringList VpnConnectionItem::iconUrls() const
{
    switch (state_) {
    case State::Invalid:
    case State::Disconnected:
        return {QStringLiteral(":shield-empty")};
    case State::Connecting:
    case State::Disconnecting:
        return {QStringLiteral(":shield-half")};
    case State::Connected:
        return {QStringLiteral(":shield-full")};
    }
    return {};  // make compilers happy
}

QString VpnConnectionItem::inputActionText() const { return text(); }

void VpnConnectionItem::addObserver(Observer *observer) { observers.insert(observer); }

void VpnConnectionItem::removeObserver(Observer *observer) { observers.erase(observer); }

void VpnConnectionItem::setState(State state)
{
    if (state_ != state)
    {
        state_ = state;
        DEBG << "State changed:" << text() << stateString(state);
        for (auto observer : observers)
            observer->notify(this);
    }
}

VpnConnectionItem::State VpnConnectionItem::state() const { return state_; }
