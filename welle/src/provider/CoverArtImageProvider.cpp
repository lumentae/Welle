#include "provider/CoverArtImageProvider.h"

namespace welle::provider {
    QImage CoverArtImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
        const auto path = m_Client->downloadCoverArt(id.toStdString());
        const QImage image(path.c_str());

        const QSize targetSize = requestedSize.isValid() ? requestedSize : QSize(56, 56);
        if (size) {
            *size = image.size();
        }

        return image.scaled(targetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    }

    void CoverArtImageProvider::setClient(medialib::client::OpenSubsonicClient *client) {
        m_Client = client;
    }
}
