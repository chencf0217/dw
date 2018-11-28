#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>
#include <vector>

using eosio::asset;
using namespace eosio;

class delaytransaction : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action
      void hi(account_name user, uint64_t id) {
		print( "Hello, ", name{user}, "id ", id);
        eosio::transaction txn{};
        txn.actions.emplace_back(
            eosio::permission_level(_self, N(active)),
            _self,
            N(delayedhi),
            std::make_tuple(id));
        txn.delay_sec = 1;
        //(sender_id, payer, replace_existed)
		// 12345678
        txn.send(id, _self);
      }

	  /// @abi action
	  void cancel(uint64_t id) {
			print( "cancel cancel cancel cancel cancel");
			cancel_deferred( id );
	  }
	  
      void delayedhi(uint64_t id) {
          print( "now() ", now());
		  auto ct = current_time();
		  print( "current_time() ", ct);
      }
	  
	  // @abi action
	  void tassetarr(std::vector<asset> args) {
	      eosio::print("tassetarr:\n");   
		  for (auto &arg :args)
		  {
			  eosio::print(arg,"\n");
		  }
	  }
};

EOSIO_ABI( delaytransaction, (hi)(cancel)(delayedhi)(tassetarr) )