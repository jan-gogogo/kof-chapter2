#include "utils.hpp"
using namespace eosio;
using namespace std;

CONTRACT kingofighter : public contract {
  public:
    using contract::contract;
    kingofighter(eosio::name receiver, eosio::name code, datastream<const char*> ds):contract(receiver, code, ds)
    {}

    [[eosio::action]]
    void signup(const name player);
    
    [[eosio::action]]
    void battle(const name player,const checksum256& seed_hash);
  
  
  private:
 
    //player
    //scope is self
    TABLE players {
      name player_account;
      asset coin;
      uint64_t counter;
      uint64_t created_at;
        
      uint64_t primary_key() const { return player_account.value;}
    };
    
    //hero
    //scope is player 
     TABLE heros {
      uint64_t id;
      string hero_name;
      uint32_t min_atk;
      uint32_t max_atk;
      uint32_t hp;
      uint64_t created_at;
      
      uint64_t primary_key() const { return id;}
    };
    
     //box
     //scope is self
     //index: player_account
     TABLE boxs {
      uint64_t id;
      name player_account;
      uint8_t level;
      uint64_t created_at;
      
      uint64_t get_player() const { return player_account.value;}
      uint64_t primary_key() const { return id;}
    };
    
    struct scoreboard{
      uint64_t round_no;
      name attacker;
      name defender;
      uint32_t damage;
      uint64_t defender_hp;
    };
    
    //game records
    //scope is self
    //index: player_account
    TABLE gamerecords {
      uint64_t game_id;
      name player_account;
      uint64_t player_counter;
      vector<scoreboard> scoreboards;
      string game_result;
      uint64_t created_at;
      
      uint64_t get_player() const { return player_account.value;}
      uint64_t primary_key() const { return game_id;}
    };
    
   using player_index = multi_index<"players"_n, players>;
   using hero_index = multi_index<"heros"_n, heros>;
   using box_index = multi_index<"boxs"_n, boxs,
    indexed_by<"byplayer"_n, const_mem_fun<boxs, uint64_t, &boxs::primary_key>>
    >;
   using game_record_index = multi_index<"gamerecords"_n, gamerecords,
    indexed_by<"byplayer"_n, const_mem_fun<gamerecords, uint64_t, &gamerecords::primary_key>>
    >;
};

