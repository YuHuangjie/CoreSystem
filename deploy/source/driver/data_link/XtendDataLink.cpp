#include "XtendDataLink.h"

BEGIN_NAMESPACE

XtendDataLink::XtendDataLink(int port, int bardrate, DataLinkID id, size_t frameSize/* = 256 */)
{
	this->port = port;
	this->bardrate = bardrate;
	ptty = nullptr;
	startSign = "xxxx";
	stopSign = "aa55";

	// make sure enough frame size
	if (frameSize < 32) {
		this->frameSize = 32;
	}
	else {
		this->frameSize = frameSize;
	}

	// allocate memory
	code = new unsigned char[frameSize];
	coderev = new unsigned char[frameSize];
//	realcode = new unsigned char[frameSize];

	this->headSize = 21;
	// initialize code
	code[0] = 126; code[1] = 0; code[2] = 0; code[3] = 16;
	code[4] = 1;   code[5] = 0; code[6] = 0; code[7] = 0;
	code[8] = 0;   code[9] = 0; code[10] = 0; code[11] = 255;
	code[12] = 255; code[13] = 255; code[14] = 254; code[15] = 0;
	code[16] = 0;
	code[17] = static_cast<unsigned char>(startSign[0]);
	code[18] = static_cast<unsigned char>(startSign[1]);
	code[19] = static_cast<unsigned char>(startSign[2]);
	code[20] = static_cast<unsigned char>(startSign[3]);


	for (size_t i = 0; i != frameSize; ++i) {
		coderev[i] = 0;
	}

	this->id = id;
}

XtendDataLink::~XtendDataLink()
{
	// clean tty resources
	CleanTTY();

	// delete other memory
	delete[] code;
	code = nullptr;
	delete[] coderev;
	coderev = nullptr;
//	delete[] realcode;
//	realcode = nullptr;
}

bool XtendDataLink::Run(void)
{
	ptty = ReadyTTY(port);
	if (ptty == NULL)
	{
		cerr << "ERROR: ready tty" << endl;
		return false;
	}

	LockTTY();

	if (SetTTYSpeed(bardrate) > 0) {
		cerr << "ERROR: SetTTYSpeed" << endl;
		return false;
	}
	if (SetTTYParity(8, 'N', 1) > 0) {
		cerr << "ERROR: SetTTYParity" << endl;
		return false;
	}

	setbuf(stdout, NULL);

	switch (id) {
    case DataLinkSender:
        t = thread(&XtendDataLink::SendThread, this);
        break;
    case DataLinkReciever:
        t = thread(&XtendDataLink::ListenThread, this);
        break;
    default:
        return false;
	}

	return true;
}

void XtendDataLink::SendThread(void)
{
    string dataSend;
    	// test frequency
    //clock_t start = clock();
    //int count = 0;

    while (true) {
        gDownMutex.lock();
        dataSend = Down2String(gDownBuffer);
        gDownMutex.unlock();
        Send(dataSend);

//      test frequency
//        if ((clock() - start) / CLOCKS_PER_SEC >= 1) {
//            cout << count << endl;
//            start = clock();
//            count = 0;
//        }
//        count+=1;
    }
}

void XtendDataLink::ListenThread(void)
{
	string dataRecv;
	bool ret;

	// test frequency
    //clock_t start = clock();
    //int count = 0;

	while (true) {
		// recieve
		ret = Recv(dataRecv);
		if (!ret) {
			continue;
		}
		ret = String2Up(dataRecv, gUpBuffer);
		if (!ret) {
			cerr << "ERROR: data link: decode recieve fail" << endl;
			break;
		}

		// test frequency
//        if ((clock() - start) / CLOCKS_PER_SEC >= 1) {
//            cout << count << endl;
//            start = clock();
//            count = 0;
//        }
//        count+=1;
	}
}

bool XtendDataLink::Stop(void)
{
	CleanTTY();
	return true;
}

bool XtendDataLink::Send(const string &str)
{
    string send = str;
    send += "aa55";
    send += string(32, ' ');

	if (ChangeString(send)) {
		SendnTTY(code, frameSize);
		for (size_t i = headSize; i != frameSize; ++i) {
			code[i] = 0;
		}
		return true;
	}
	else {
		return false;
	}
}

bool XtendDataLink::Recv(std::string &str)
{
	int length = RecvnTTY(coderev, 32, 0.1);

	if (length < 0) {
        str = "";
        return false;
	}
	else {
        str = string((char*)coderev, length);
        return true;
	}
}

bool XtendDataLink::SetDownData(const DATALINK_DOWN_FORMAT &data)
{
    //gDownMutex.lock();
	gDownBuffer = data;
	//gDownMutex.unlock();

	return true;
}

bool XtendDataLink::GetUpData(DATALINK_UP_FORMAT &data)
{
    data = gUpBuffer;

	return true;
}

string XtendDataLink::Down2String(const DATALINK_DOWN_FORMAT &data) const
{
	string ret = "";

	ret += Converter::ConvertInt32(data.roll);
	ret += Converter::ConvertInt32(data.pitch);
	ret += Converter::ConvertInt32(data.yaw);
	ret += Converter::ConvertInt32(data.throttle);

	ret += Converter::ConvertFloat(data.imu_roll);
	ret += Converter::ConvertFloat(data.imu_pitch);
	ret += Converter::ConvertFloat(data.imu_yaw);

	ret += Converter::ConvertFloat(data.gps_lontitude);
	ret += Converter::ConvertFloat(data.gps_latitude);
	ret += Converter::ConvertFloat(data.gps_altitude);
	ret += Converter::ConvertFloat(data.gps_height);

	ret += Converter::ConvertFloat(data.pressure_altitude);

	ret += Converter::ConvertFloat(data.u_x);
	ret += Converter::ConvertFloat(data.u_y);
	ret += Converter::ConvertFloat(data.u_z);

	ret += Converter::ConvertFloat(data.omega_x);
	ret += Converter::ConvertFloat(data.omega_y);
	ret += Converter::ConvertFloat(data.omega_z);

	ret += Converter::ConvertFloat(data.a_x);
	ret += Converter::ConvertFloat(data.a_y);
	ret += Converter::ConvertFloat(data.a_z);

	ret += Converter::ConvertInt32(data.param_type);
	ret += string(data.param, sizeof(data.param));

	return ret;
}

string XtendDataLink::Up2String(const DATALINK_UP_FORMAT &data) const
{
	string ret = "";

	ret += Converter::ConvertInt32(data.roll);
	ret += Converter::ConvertInt32(data.pitch);
	ret += Converter::ConvertInt32(data.yaw);
	ret += Converter::ConvertInt32(data.throttle);

	ret += string(data.options, sizeof(data.options));

	ret += Converter::ConvertInt32(data.param_type);
	ret += string(data.param, sizeof(data.param));

	return ret;
}

bool XtendDataLink::String2Down(const string &str, DATALINK_DOWN_FORMAT &data) const
{
	size_t totalSize = 108;
	if (str.size() != totalSize) {
		cerr << "ERROR: decode down format: string size incompatible" << endl;
		return false;
	}

	size_t pos = 0;
	bool success = false;

	success = Converter::DecodeInt32(str.substr(pos, 4), data.roll);	pos += 4;
	success = Converter::DecodeInt32(str.substr(pos, 4), data.pitch);	pos += 4;
	success = Converter::DecodeInt32(str.substr(pos, 4), data.yaw);		pos += 4;
	success = Converter::DecodeInt32(str.substr(pos, 4), data.throttle); pos += 4;

	success = Converter::DecodeFloat(str.substr(pos, 4), data.imu_roll); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.imu_pitch); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.imu_yaw); pos += 4;

	success = Converter::DecodeFloat(str.substr(pos, 4), data.gps_lontitude); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.gps_latitude); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.gps_altitude); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.gps_height); pos += 4;

	success = Converter::DecodeFloat(str.substr(pos, 4), data.pressure_altitude); pos += 4;

	success = Converter::DecodeFloat(str.substr(pos, 4), data.u_x); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.u_y); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.u_z); pos += 4;

	success = Converter::DecodeFloat(str.substr(pos, 4), data.omega_x); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.omega_y); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.omega_z); pos += 4;

	success = Converter::DecodeFloat(str.substr(pos, 4), data.a_x); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.a_y); pos += 4;
	success = Converter::DecodeFloat(str.substr(pos, 4), data.a_z); pos += 4;

	int32_t type;
	success = Converter::DecodeInt32(str.substr(pos, 4), type); pos += 4;
	data.param_type = static_cast<DATALINK_PARAM_TYPE>(type);

	for (int i = 0; i != sizeof(data.param); ++i) {
		data.param[i] = str[pos++];
	}

	return true;
}

bool XtendDataLink::String2Up(const string &str, DATALINK_UP_FORMAT &data) const
{
	size_t totalSize = 44;
	if (str.size() != totalSize) {
		cerr << "ERROR: decode up data: string size incompatible" << endl;
		return false;
	}

	size_t pos = 0;
	bool success = false;

	success = Converter::DecodeInt32(str.substr(pos, 4), data.roll); pos += 4;
	success = Converter::DecodeInt32(str.substr(pos, 4), data.pitch); pos += 4;
	success = Converter::DecodeInt32(str.substr(pos, 4), data.yaw); pos += 4;
	success = Converter::DecodeInt32(str.substr(pos, 4), data.throttle); pos += 4;

	for (int i = 0; i != sizeof(data.options); ++i)
		data.options[i] = str[pos++];

	int type;
	success = Converter::DecodeInt32(str.substr(pos, 4), type); pos += 4;
	data.param_type = static_cast<DATALINK_PARAM_TYPE>(type);

	for (int i = 0; i != sizeof(data.param); ++i)
		data.param[i] = str[pos++];

	return true;
}


bool XtendDataLink::ChangeString(const string &getin)
{
	if (getin.length() > frameSize - headSize)
	{
		return false;
	}

	int i = headSize;	// start from 21
	int sum = 0;
	for (size_t j = 0; j < getin.length(); j++) {
		code[i] = (unsigned char)getin[j];
		i++;
		sum = sum + (int)getin[j];
	}
	int num = 18 + getin.length();
	code[1] = 0;
	code[2] = num;
	int dev = 243 - sum;
	dev = dev - 480;
	unsigned char a;
	if (dev > 0 && dev == 0) {
		a = dev % 16 + dev / 16 % 16 * 16;
	}
	else {
		dev = dev*(-1);
		a = dev % 16 + dev / 16 % 16 * 16;
		a = 255 - a + 1;
		if (a > 255) {
			a = 0;
		}
	}
	code[i] = a;

    i++;
    for(;i<60;i++)
        code[i]=0;

	return true;
}


/****************************************************
 *			serial library
 ***************************************************/
TTY_INFO* XtendDataLink::ReadyTTY(int id)
{
	TTY_INFO *ptty;

    ptty = (TTY_INFO *)malloc(sizeof(TTY_INFO));
    if(ptty == NULL)
        return NULL;
    memset(ptty,0,sizeof(TTY_INFO));
    pthread_mutex_init(&ptty->mt,NULL);
    sprintf(ptty->name,"/dev/ttyUSB%d",id);
    //

    // open and config serial port

    ptty->fd = open(ptty->name, O_RDWR | O_NOCTTY |O_NDELAY);
    if (ptty->fd <0)
    {
        free(ptty);
        return NULL;
    }
    //

    // get and save original configuration

    tcgetattr(ptty->fd,&ptty->otm);
    return ptty;
}

int XtendDataLink::CleanTTY(void)
{
	if(ptty->fd>0)
    {
        tcsetattr(ptty->fd,TCSANOW,&ptty->otm);
        close(ptty->fd);
        ptty->fd = -1;
        free(ptty);
        ptty = NULL;
    }

    return 0;
}

int XtendDataLink::SetTTYSpeed(int speed)
{
	bzero(&ptty->ntm, sizeof(ptty->ntm));
    tcgetattr(ptty->fd,&ptty->ntm);
    ptty->ntm.c_cflag = /*CS8 |*/ CLOCAL | CREAD;

    switch(speed)
    {
    case 300:
        ptty->ntm.c_cflag |= B300;
        break;
    case 1200:
        ptty->ntm.c_cflag |= B1200;
        break;
    case 2400:
        ptty->ntm.c_cflag |= B2400;
        break;
    case 4800:
        ptty->ntm.c_cflag |= B4800;
        break;
    case 9600:
        ptty->ntm.c_cflag |= B9600;
        break;
    case 19200:
        ptty->ntm.c_cflag |= B19200;
        break;
    case 38400:
        ptty->ntm.c_cflag |= B38400;
        break;
    case 115200:
        ptty->ntm.c_cflag |= B115200;
        break;
    }
    ptty->ntm.c_iflag = IGNPAR;
    ptty->ntm.c_oflag = 0;
    //

    //

    tcflush(ptty->fd, TCIFLUSH);
    tcsetattr(ptty->fd,TCSANOW,&ptty->ntm);
    //

    //

    return 0;
}

int XtendDataLink::SetTTYParity(int databits, char parity, int stopbits)
{
	// get serial configuration

    if( tcgetattr(ptty->fd,&ptty->ntm) != 0)
    {
        printf("SetupSerial [%s]\n",ptty->name);
        return 1;
    }

    bzero(&ptty->ntm, sizeof(ptty->ntm));
    ptty->ntm.c_cflag = CS8 | CLOCAL | CREAD;
    ptty->ntm.c_iflag = IGNPAR;
    ptty->ntm.c_oflag = 0;
    //

    // config serial parameters

    ptty->ntm.c_cflag &= ~CSIZE;
    switch (databits)
    { // set data bits

    case 7:
        ptty->ntm.c_cflag |= CS7;
        break;
    case 8:
        ptty->ntm.c_cflag |= CS8;
        break;
    default:
        printf("Unsupported data size\n");
        return 5;
    }
    //

    //

    switch (parity)
    { // 设置奇偶校验位数

    case 'n':
    case 'N':
        ptty->ntm.c_cflag &= ~PARENB; /* Clear parity enable */
        ptty->ntm.c_iflag &= ~INPCK; /* Enable parity checking */
        break;
    case 'o':
    case 'O':
        ptty->ntm.c_cflag |= (PARODD|PARENB); /* 设置为奇效验*/
        ptty->ntm.c_iflag |= INPCK; /* Disnable parity checking */
        break;
    case 'e':
    case 'E':
        ptty->ntm.c_cflag |= PARENB; /* Enable parity */
        ptty->ntm.c_cflag &= ~PARODD; /* 转换为偶效验*/
        ptty->ntm.c_iflag |= INPCK; /* Disnable parity checking */
        break;
    case 'S':
    case 's': /*as no parity*/
        ptty->ntm.c_cflag &= ~PARENB;
        ptty->ntm.c_cflag &= ~CSTOPB;
        break;
    default:
        printf("Unsupported parity\n");
        return 2;
    }
    //

    // set stop bits

    switch (stopbits)
    {
    case 1:
        ptty->ntm.c_cflag &= ~CSTOPB;
        break;
    case 2:
        ptty->ntm.c_cflag |= CSTOPB;
        break;
    default:
        printf("Unsupported stop bits\n");
        return 3;
    }
    //

    //

    ptty->ntm.c_lflag = 0;
    ptty->ntm.c_cc[VTIME] = 0; // inter-character timer unused

    ptty->ntm.c_cc[VMIN] = 1; // blocking read until 1 chars received

    tcflush(ptty->fd, TCIFLUSH);
    if (tcsetattr(ptty->fd,TCSANOW,&ptty->ntm) != 0)
    {
        printf("SetupSerial \n");
        return 4;
    }

    return 0;
}

int XtendDataLink::RecvnTTY(unsigned char *pbuf, int size, const float &timeout)
{
	int bytes = 0;
	int ret = 0;

	unsigned char *buf = new unsigned char[size];
	int index = 0;
	int startIndex = 0;
	int stopIndex = 0;
	string recvString = "";
	bool startFound =false;
	clock_t start = clock();

    bzero(pbuf,sizeof(unsigned char)*size);

    while (stopIndex == 0) {
        if ((double)(clock() - start) / CLOCKS_PER_SEC > timeout) {
            return -1;
        }

        ioctl(ptty->fd, FIONREAD, &bytes);
        if(bytes > 0) {

           pthread_mutex_lock(&ptty->mt);
           ret = read(ptty->fd, buf, 32);
           pthread_mutex_unlock(&ptty->mt);
        }
        else {
            continue;
        }

        recvString += string((char*)buf, ret);
        // find start sign string
        if (!startFound) {
        	index = recvString.find(startSign);

        	if (index == string::npos) {
        		continue;
        	}
        	else {
        		startIndex = index + startSign.length();
        		startFound = true;
        	}
        }

        if (!startFound) {
        	continue;
        }

        // find stop sign string
        index = recvString.find(stopSign, startIndex);
        if (index == string::npos) {
        	continue;
        }
        else {
        	stopIndex = index;
        }
    }

    int i = 0;
    int j = startIndex;

    while (j < stopIndex) {
    	pbuf[i++] = recvString[j++];
    }

    delete[] buf;

    return stopIndex - startIndex;
}

int XtendDataLink::SendnTTY(unsigned char *pbuf, int size)
{
	int ret,nleft;
    unsigned char *ptmp;

    ret = 0;
    nleft = size;
    ptmp = pbuf;


    while(nleft>0)
    {
        pthread_mutex_lock(&ptty->mt);
        ret = write(ptty->fd,ptmp,nleft);
        pthread_mutex_unlock(&ptty->mt);

        if(ret >0)
        {
            nleft -= ret;
            ptmp += ret;
        }
        //usleep(100);

    }


    return size - nleft;
}

/** \brief
 *
 * \param void
 * \return int
 *
 */
int XtendDataLink::LockTTY(void)
{
	if(ptty->fd < 0)
    {
        return 1;
    }

    return flock(ptty->fd,LOCK_EX);
}

int XtendDataLink::UnlockTTY(void)
{
    if(ptty->fd < 0)
    {
        return 1;
    }

    return flock(ptty->fd,LOCK_UN);
}

END_NAMESPACE
