#include <eosio/crypto.hpp>
#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/singleton.hpp>
#include <eosio/time.hpp>
#include <eosio/print.hpp>
#include <vector>
using namespace eosio;
using namespace std;


/**
 * 剪切字符串
 * @param input 字符串输入
 * @param count 需要剪切的段数
 */
vector<string> cut_str(const string &input,const size_t count){
  const size_t part_len = input.size() / (count + (count & 1));
  vector<string> vec;
  size_t idx = 0;
  for (size_t i = 0; i < count; i++) {
    string part = input.substr(idx,part_len);
    idx += part_len;
    vec.emplace_back(part);
  }
  return vec;
}

