#include <QCoreApplication>
#include <google/protobuf/util/json_util.h>

#ifdef __cplusplus
extern "C"{
#endif

#include <sodium.h>
#include <opus.h>

#ifdef __cplusplus
}
#endif

#define SAMPLE_RATE 48000
#define CHANNELS 2
#define APPLICATION OPUS_APPLICATION_AUDIO

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::string version = google::protobuf::internal::VersionString(1234);

    qDebug(version.c_str());

    OpusEncoder *encoder;
    int err;

    encoder = opus_encoder_create(SAMPLE_RATE, CHANNELS, APPLICATION, &err);

    if (err < 0)
    {
        fprintf(stderr, "failed to create an encoder: %s\n", opus_strerror(err));
        return EXIT_FAILURE;
    }

    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized, it is not safe to use */
        return 1;
    }

    google::protobuf::ShutdownProtobufLibrary();
        
    qDebug("end");

    return 0;
}
