#pragma once

#include <QQuickImageProvider>

#include "client/OpenSubsonicClient.h"

namespace welle::provider {
    class CoverArtImageProvider : public QQuickImageProvider {
    public:
        CoverArtImageProvider() : QQuickImageProvider(Image)
        {
        }

        QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize) override;
        void setClient(medialib::client::OpenSubsonicClient* client);

    private:
        medialib::client::OpenSubsonicClient* m_Client;
    };
}
