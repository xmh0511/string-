//
// Created by dy2018 on 18-4-3.
//

#ifndef WEBSTR_STRING_HPP
#define WEBSTR_STRING_HPP
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <fstream>
#include <sstream>
#include<locale>
#include <codecvt>
enum  class RegMode:std::size_t
{
    SIGNLE,
    GLOBAL
};
enum class writeFileMode:std::size_t
{
    FULL,
    ADD
};
class String:public std::string
{
    friend std::ostream& operator<<(std::ostream& out,const String& str);
public:
    String():std::string()
    {

    }
    String(const char* str):std::string(str)
    {

    }
    String(const std::string& str):std::string(str)
    {

    }
    ~String()
    {

    }
public:
    String(const char* str,std::string::size_type n):std::string(str,n)
    {

    }
    bool operator ==(const String& str) const
    {
        return this->to_stdstring()==str.to_stdstring();
    }
    String operator +(const String& str) const
    {
          String temp;
          temp.append(*this).append(str);
          return temp;
    }

public:
    std::string to_stdstring() const
    {
        return std::string(this->c_str());
    }
    std::vector<String> split(String splitstr) const
    {
        std::vector<String> Vect;
        const char* head =this->data();
        const char* ptr = head;
        char special = splitstr[0];
        const int compareSize = splitstr.size();
        while(*ptr!='\0')
        {
            if(*ptr==special)
            {
                String possibleSpecialStr(ptr,compareSize);
                if(possibleSpecialStr==splitstr)
                {
                    Vect.push_back(std::move(String(head,ptr-head)));
                    head = ptr+compareSize;
                    ptr+=compareSize;
                }
            }
            ptr++;
        }
        Vect.push_back(std::move(String(head,ptr-head)));
        return std::move(Vect);
    }
    String& join(std::vector<String>& Vect,String splitstr)
    {
        for(auto iter=Vect.begin();iter!=Vect.end();iter++)
        {
            if(iter!=Vect.end()-1)
            {
                std::cout<<*iter<<std::endl;
                (*this)+=*iter+splitstr;
                continue;
            }
            (*this)+=*iter;
        }
        return *this;
    }
    String& replace(String key,String rp,RegMode mode =RegMode::SIGNLE)
    {
            const char* head = this->data();
            const char* data = this->data();
            const std::size_t key_size = key.size();
            while(*data!='\0')
            {
                if(*data==key[0])
                {
                    if(String(data,key_size)==key)
                    {
                        String before(head,data-head);
                        String after(data+key_size,this->size());
                        //std::cout<<(before+rp+after)<<std::endl;
                        *this = before+rp+after;
                        head = this->data();
                        data = this->data()+before.size()+rp.size();
                        if(mode==RegMode::SIGNLE)
                        {
                            break;
                        }else if(mode==RegMode::GLOBAL){
                            continue;
                        }else{
                            break;
                        }
                    }
                }
                data++;
            }
        return *this;
    }
    bool contain(const String& str) const
    {
        auto pos = this->find(str.c_str());
        return pos!=std::string::npos?true:false;
    }
public:
    int to_int() const
    {
        return std::atoi(this->c_str());
    }

    double to_double() const
    {
       return std::atof(this->c_str());
    }
    template<typename T>
    String& format_number(T number)
    {
        *this = std::to_string(number);
        return *this;
    }
    String to_lower() const
    {
        String temp;
        for(auto iter:*this)
        {
            temp+=std::tolower(iter);
        }
        return temp;
    }
    String to_upper() const
    {
        String temp;
        for(auto iter:*this)
        {
            temp+=std::toupper(iter);
        }
        return temp;
    }
    String& sort()
    {
        auto char_size = this->size();
        sort_by_ascii(&(*this)[0],0,char_size-1);
        return *this;
    }
public:
    bool write_file(const String& fileName,writeFileMode mode = writeFileMode::FULL) const
    {
        auto write_mode = mode==writeFileMode::FULL?std::ios_base::out:std::ios_base::app;
        std::ofstream fileHandler(fileName.c_str(),std::ios_base::binary | write_mode);
        fileHandler<<this->c_str();
        return true;
    }

    String& read_file(const String& fileName)
    {
        std::ifstream fileHandler(fileName.c_str(),std::ios_base::binary);
        std::stringstream buff;
        buff<<fileHandler.rdbuf();
        *this = buff.str();
        return  *this;
    }

protected:
    template<class Facet>
    struct deletable_facet : Facet
    {
        template<class ...Args>
        deletable_facet(Args&& ...args)
                : Facet(std::forward<Args>(args)...) {}
        ~deletable_facet() {}
    };
public:
      String url_encode() noexcept {
        static auto hex_chars = "0123456789ABCDEF";
        String result;
        result.reserve(this->size()); // Minimum size of result

        for (auto &chr : *this) {
            if (!((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || chr == '-' || chr == '.' || chr == '_' || chr == '~'))
                result += String("%") + hex_chars[static_cast<unsigned char>(chr) >> 4] + hex_chars[static_cast<unsigned char>(chr) & 15];
            else
                result += chr;
        }
        return result;
    }

     String url_decode() noexcept {
        String result;
        result.reserve(this->size() / 3 + (this->size() % 3)); // Minimum size of result

        for (std::size_t i = 0; i < this->size(); ++i) {
            auto &chr = this->operator[](i);
            if (chr == '%' && i + 2 < this->size()) {
                auto hex = this->substr(i + 1, 2);
                auto decoded_chr = static_cast<char>(std::strtol(hex.c_str(), nullptr, 16));
                result += decoded_chr;
                i += 2;
            }
            else if (chr == '+')
                result += ' ';
            else
                result += chr;
        }
        return result;
    }

    bool is_url_encode()
    {
        return this->find("%") != std::string::npos || this->find("+") != std::string::npos;
    }

    String utf8_to_gbk()
    {
        return utf16_to_gbk(utf8_to_utf16(*this));
    }

    String gbk_to_utf8()
    {
        return utf16_to_utf8(gbk_to_utf16(*this));
    }

private:

    std::wstring gbk_to_utf16(const std::string &gbk)
    {
        typedef deletable_facet<std::codecvt_byname<wchar_t, char, std::mbstate_t>> gbfacet_t;
        std::wstring_convert<gbfacet_t> conv(new gbfacet_t(GBK_LOCALE_NAME));
        std::wstring utf16 = conv.from_bytes(gbk);
        return utf16;
    }

    String utf16_to_gbk(const std::wstring &utf16)
    {
        typedef deletable_facet<std::codecvt_byname<wchar_t, char, std::mbstate_t>> gbfacet_t;
        std::wstring_convert<gbfacet_t> conv(new gbfacet_t(GBK_LOCALE_NAME));

        String gbk = conv.to_bytes(utf16);
        return std::move(gbk);
    }

    std::wstring utf8_to_utf16(const std::string &utf8)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        std::wstring utf16 = conv.from_bytes(utf8);
        return utf16;
    }

    String utf16_to_utf8(const std::wstring &utf16)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        String utf8 = conv.to_bytes(utf16);
        return utf8;
    }

private:
    void sort_by_ascii(char* ptr,long begin,long end)
    {
        if(begin<end)
        {
            long left_iter = begin;
            long right_iter = end;
            char compare = ptr[begin];
            while(left_iter!=right_iter)
            {
                while(left_iter<right_iter)
                {
                    if(ptr[right_iter]<compare)
                    {
                        ptr[left_iter] = ptr[right_iter];
                        break;
                    }
                    --right_iter;
                }

                while(left_iter<right_iter)
                {
                    if(ptr[left_iter]>compare)
                    {
                        ptr[right_iter] = ptr[left_iter];
                        break;
                    }
                    ++left_iter;
                }
            }
            ptr[left_iter] = compare;
            sort_by_ascii(ptr,begin,left_iter-1);
            sort_by_ascii(ptr,left_iter+1,end);
        }
    }
private:
#ifdef _MSC_VER
    const char* GBK_LOCALE_NAME = ".936";
#else
    const char* GBK_LOCALE_NAME = "zh_CN.GBK";
#endif
};
std::ostream& operator<<(std::ostream& out,const String& str)
{
    out<<str.c_str();
    return out;
}
#endif //WEBSTR_STRING_HPP
