#include "VoipManager.h"
#include "VoipAccount.h"
#include "VoipCall.h"
#include <QTime>

namespace voip {

VoipManager::VoipManager(QObject *parent)
    : QObject(parent),
      acc(new VoipAccount(this))
{
    // Endpoint init
    try {
        ep.libCreate();
    } catch (pj::Error &err) {
        // FIXME: handle this
        Q_UNUSED(err);
    }
    pj::EpConfig ep_config;
    ep_config.logConfig.level = 5;
    ep_config.uaConfig.maxCalls = 1;
    ep.libInit(ep_config);

    // Transport init
    QTime time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    int n = qrand() % 10000;
    qDebug() << n << endl;
//    while (!getTcpPortState(5060)) {
//        QTime time = QTime::currentTime();
//        qsrand(time.msec() + time.second() * 1000);
//        int n = qrand() % 10000;
//        qDebug() << n << endl;
//    }
    pj::TransportConfig trans_config;
    trans_config.port = 5060;
    ep.transportCreate(PJSIP_TRANSPORT_TCP, trans_config);

    // Start library
    ep.libStart();
    qDebug() << "PJSUA started!" << endl;

    callState = "normal";
    connect(acc, SIGNAL(incomingCall(pj::OnIncomingCallParam*)), this, SLOT(onIncomingCall(pj::OnIncomingCallParam*)));

    // init account
    initAccount();
}

VoipManager::~VoipManager()
{
    if(acc)
        delete acc;
}

void VoipManager::initAccount()
{
    acc->registerAsClient();
}

void VoipManager::makeAudioCall()
{
    pj::Call *newCall = new VoipCall(*acc);
    this->acc->calls.append(newCall);
    connect((VoipCall*)newCall, &VoipCall::callStateChanged,this,&VoipManager::onCallStateChanged,Qt::UniqueConnection);

    pj::CallOpParam p(true);
    p.opt.audioCount = 1;
    p.opt.videoCount = 0;
    try {
        newCall->makeCall("sip:138941@47.91.217.14;transport=tcp", p);
        qDebug() << "*** Making call" << endl;
    } catch(...) {
        qDebug() << "*** Making call failed" << endl;
    }

    pj::CallInfo ci = newCall->getInfo();
    if (ci.state == PJSIP_INV_STATE_CONFIRMED) {
        setState("CONFIRMED");
    }
}

void VoipManager::hangup()
{
    ep.hangupAllCalls();
    qDebug() << "*** Hanging up the call" << endl;
}

void VoipManager::answer()
{
    pj::Call *newCall = acc->calls[0];
    connect((VoipCall*)newCall, &VoipCall::callStateChanged,this,&VoipManager::onCallStateChanged,Qt::UniqueConnection);
    pj::CallOpParam callOpParam;
    callOpParam.statusCode = PJSIP_SC_OK;
    newCall->answer(callOpParam);
}

void VoipManager::reject()
{
    pj::Call *newCall = acc->calls[0];

    pj::CallOpParam callOpParam;
    callOpParam.statusCode = PJSIP_SC_DECLINE;
    newCall->hangup(callOpParam);
    newCall = nullptr;
}

void VoipManager::setVolume(float volume)
{
    if (acc->calls.count() != 0){
        for (unsigned i = 0; i < (acc->calls.count()); i++){
            VoipCall *newCall = (VoipCall *)acc->calls[i];
            newCall->setVolume(volume);
        }
    }
}

QString VoipManager::state() const
{
    return callState;
}

void VoipManager::setState(const QString &state)
{
    callState = state;
    emit stateChanged(callState);
}

bool VoipManager::getTcpPortState(int port)
{
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    tcpSocket->bind(port);
//    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
//    sockaddr_in addr;
//    addr.sin_family = AF_INET;
//    addr.sin_port = htons(port);
//    addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    bind(s,(LPSOCKADDR)&addr, sizeof(addr));
    if (tcpSocket->error() == QAbstractSocket::AddressInUseError) {
        return false;
    } else {
        tcpSocket->close();
        return true;
//        closesocket(s);
//        bool bDontLinger = false;
//        setsockopt(s, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(bool));
//        return true;
    }
}

void VoipManager::onIncomingCall(pj::OnIncomingCallParam *iprm)
{
    // append to call active calls
    activeCallParams.append(iprm);
    setState("INCOMING");
    qDebug() << "Receiving signals succeed!" << endl;
}

void VoipManager::onCallStateChanged(const QString &callState)
{
    setState(callState);
}
}
