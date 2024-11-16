#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) 
    : _buf(), _capacity(capacity), _read_cnt(0), _write_cnt(0), end_byte_flag(false) {}

size_t ByteStream::write(const string &data) {
    size_t can_write = _capacity - buffer_size();
    size_t byte_len = min(can_write, data.size());
    for(size_t i = 0; i < byte_len; i++)
    {
        _buf.push_back(data[i]);
    }
    _write_cnt += byte_len;
    return byte_len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t byte_len = min(len, buffer_size());
    string tmp_buf = "";
    for(size_t i = 0; i < byte_len; i++)
    {
        tmp_buf += _buf[i];
    }

    return tmp_buf;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    if(len > buffer_size())
    {
        set_error();
        return;
    }
    for(size_t i = 0; i < len; i++)
    {
        _buf.pop_front();
    }
    _read_cnt += len;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string read_buf = "";
    if(len > buffer_size())
    {
        set_error();
        return read_buf;
    }
    for(size_t i = 0; i < len; i++)
    {
        read_buf += _buf[i];
        _buf.pop_front();
    }
    _read_cnt += len;
    return read_buf;
}

void ByteStream::end_input() {
    end_byte_flag = true;
}

bool ByteStream::input_ended() const { 
    return end_byte_flag;
}

size_t ByteStream::buffer_size() const { 
    return _buf.size();
}

bool ByteStream::buffer_empty() const { 
    return _buf.empty(); 
}

bool ByteStream::eof() const { 
    return end_byte_flag && buffer_empty();    
}

size_t ByteStream::bytes_written() const { 
    return _write_cnt;
}

size_t ByteStream::bytes_read() const { 
    return _read_cnt;
}

size_t ByteStream::remaining_capacity() const { 
    return _capacity - buffer_size(); 
}
