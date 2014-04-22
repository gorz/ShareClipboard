#include "clipboardmanager.h"

ClipboardManager::ClipboardManager(QObject *parent)
    : QObject(parent)
    , m_clipboard(QApplication::clipboard())
{
    connect(m_clipboard,&QClipboard::changed,this,&ClipboardManager::onClipboardChanged);
}

void ClipboardManager::clipboardContentArrived(QString text)
{
    m_clipboard->blockSignals(true);
    m_clipboard->setText(text);
    m_clipboard->blockSignals(false);
    Logger::instance()<<TimeStamp()<<"Clipboard content arrived.\n";
}

void ClipboardManager::onClipboardChanged(QClipboard::Mode mode)
{
    if(mode!=QClipboard::Clipboard)
        return;
    emit sendClipboard(m_clipboard->text());
    Logger::instance()<<TimeStamp()<<"Will send clipboard.\n";
}
