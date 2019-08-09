#include "voipcall.h"
#include <iostream>

namespace voip {

voipCall::voipCall(pj::Account &acc, int call_Id)
    : pj::Call{acc, call_Id},
      account{static_cast<voipAccount *>(&acc)},
      callId{call_Id}
{
    wav_player = NULL;
}

voipCall::~voipCall()
{
    if (wav_player)
        delete wav_player;
}

void voipCall::onCallState(pj::OnCallStateParam &prm)
{
    Q_UNUSED(prm);

    pj::CallInfo ci = getInfo();
    std::cout << "*** Call: " << ci.stateText << std::endl;
    if(ci.state == PJSIP_INV_STATE_DISCONNECTED) {
        account -> removeCall(this);
        delete this;
    }
}

void voipCall::onCallMediaState(pj::OnCallMediaStateParam &prm)
{
    Q_UNUSED(prm);
    pj::CallInfo ci = getInfo();

    for (int i = 0; i < ci.media.size(); i++) {
        if (ci.media[i].type == PJMEDIA_TYPE_AUDIO && getMedia(i)) {
            // 语音通话
            pj::AudioMedia aud_med;
            pj::AudioMedia& play_dev_med =
                    pj::Endpoint::instance().audDevManager().getPlaybackDevMedia();

            try {
                aud_med = getAudioMedia(i);
            } catch (...) {
                qDebug() << "Failed to get audio media" << endl;
                return;
            }

            if (!wav_player) {
                wav_player = new pj::AudioMediaPlayer();
                try {
                    wav_player->createPlayer("E:\pjproject-2.9\tests\pjsua\wavs\input.16.wav", 0);
                } catch (...) {
                    std::cout << "Failed opening wav file"  << std::endl;
                    delete wav_player;
                    wav_player = NULL;
                }
            }

            if (wav_player) {
                wav_player->startTransmit(aud_med);
            }
            aud_med.startTransmit(play_dev_med);
        } else if (ci.media[i].type == PJMEDIA_TYPE_VIDEO && (ci.media[i].dir & PJMEDIA_DIR_DECODING)) {
//            pjsua_vid_win_info wi;
//            pjsua_vid_win_get_info(ci.media[i].videoIncomingWindowId, &wi);

//            qDebug() << "found video window, start video...";
        }
    }

    //    pj::AudioMedia aud_med;
    //    pj::AudioMedia& play_dev_med =
    //            pj::Endpoint::instance().audDevManager().getPlaybackDevMedia();

    //    try {
    //        // Get the first audio media
    //        aud_med = getAudioMedia(-1);
    //    } catch(...) {
    //        qDebug() << "Failed to get audio media" << endl;
    //        return;
    //    }

    //    if (!wav_player) {
    //        wav_player = new pj::AudioMediaPlayer();
    //        try {
    //            wav_player->createPlayer("E:\pjproject-2.9\tests\pjsua\wavs\input.16.wav", 0);
    //        } catch (...) {
    //            std::cout << "Failed opening wav file" << std::endl;
    //            delete wav_player;
    //            wav_player = NULL;
    //        }
    //    }

    //    // This will connect the wav file to the call audio media
    //    if (wav_player)
    //        wav_player->startTransmit(aud_med);

    //    // And this will connect the call audio media to the sound device/speaker
    //    aud_med.startTransmit(play_dev_med);
}

void voipCall::onCallTransferRequest(pj::OnCallTransferRequestParam &prm)
{
    /* Create new Call for call transfer */
    prm.newCall = new voipCall(*account);
}

void voipCall::onCallReplaced(pj::OnCallReplacedParam &prm)
{
    /* Create new Call for call replace */
    prm.newCall = new voipCall(*account, prm.newCallId);
}

}

