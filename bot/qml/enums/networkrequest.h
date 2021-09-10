#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

#include <QObject>
#include <QNetworkRequest>

class NetworkRequest : public QObject
{
    Q_OBJECT

public:
    enum KnownHeaders {
        ContentTypeHeader,
        ContentLengthHeader,
        LocationHeader,
        LastModifiedHeader,
        CookieHeader,
        SetCookieHeader,
        ContentDispositionHeader,  // added for QMultipartMessage
        UserAgentHeader,
        ServerHeader,
        IfModifiedSinceHeader,
        ETagHeader,
        IfMatchHeader,
        IfNoneMatchHeader
    };
    Q_ENUM(KnownHeaders)

    enum Attribute {
        HttpStatusCodeAttribute,
        HttpReasonPhraseAttribute,
        RedirectionTargetAttribute,
        ConnectionEncryptedAttribute,
        CacheLoadControlAttribute,
        CacheSaveControlAttribute,
        SourceIsFromCacheAttribute,
        DoNotBufferUploadDataAttribute,
        HttpPipeliningAllowedAttribute,
        HttpPipeliningWasUsedAttribute,
        CustomVerbAttribute,
        CookieLoadControlAttribute,
        AuthenticationReuseAttribute,
        CookieSaveControlAttribute,
        MaximumDownloadBufferSizeAttribute, // internal
        DownloadBufferAttribute, // internal
        SynchronousRequestAttribute, // internal
        BackgroundRequestAttribute,
#if QT_DEPRECATED_SINCE(5, 15)
        SpdyAllowedAttribute,
        SpdyWasUsedAttribute,
#endif // QT_DEPRECATED_SINCE(5, 15)
        EmitAllUploadProgressSignalsAttribute = BackgroundRequestAttribute + 3,
        FollowRedirectsAttribute Q_DECL_ENUMERATOR_DEPRECATED_X("Use RedirectPolicyAttribute"),
        Http2AllowedAttribute,
        Http2WasUsedAttribute,
#if QT_DEPRECATED_SINCE(5, 15)
        HTTP2AllowedAttribute Q_DECL_ENUMERATOR_DEPRECATED_X("Use Http2AllowedAttribute") = Http2AllowedAttribute,
        HTTP2WasUsedAttribute Q_DECL_ENUMERATOR_DEPRECATED_X("Use Http2WasUsedAttribute"),
#endif // QT_DEPRECATED_SINCE(5, 15)
        OriginalContentLengthAttribute,
        RedirectPolicyAttribute,
        Http2DirectAttribute,
        ResourceTypeAttribute, // internal
        AutoDeleteReplyOnFinishAttribute,

        User = 1000,
        UserMax = 32767
    };
    Q_ENUM(Attribute)

    enum CacheLoadControl {
        AlwaysNetwork,
        PreferNetwork,
        PreferCache,
        AlwaysCache
    };
    Q_ENUM(CacheLoadControl)

    enum LoadControl {
        Automatic = 0,
        Manual
    };
    Q_ENUM(LoadControl)

    enum Priority {
        HighPriority = 1,
        NormalPriority = 3,
        LowPriority = 5
    };
    Q_ENUM(Priority)

    enum RedirectPolicy {
        ManualRedirectPolicy,
        NoLessSafeRedirectPolicy,
        SameOriginRedirectPolicy,
        UserVerifiedRedirectPolicy
    };
    Q_ENUM(RedirectPolicy)

    enum TransferTimeoutConstant {
        DefaultTransferTimeoutConstant = 30000
    };
    Q_ENUM(TransferTimeoutConstant)
};

#endif // NETWORKREQUEST_H
