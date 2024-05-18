class BentPipe : protected Demod
{
public:
    BentPipe();
    ~BentPipe();
private:
    int receiveBuffer(int16_t &buffer);

}
