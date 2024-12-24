

### Bitcoin Basic

* TXO: Transaction-Output, each TXO represents a coin, containing the information of (owner, value) for the coin. Each TXO is a **(public key, value)** pair.
* UTXO: (unspent transaction outputs): A transaction can consumes only the Unspent TXOs.

==The secret key is the only thing that can be used to own and spend a TXO/coin.==

>  Each transaction consumes existing TXOs/coins and generates new TXOs/coins. The value in the consumed/old coins are transferred to the generated/new coins. Thus, each TXO/coin can be consumed/spent only one time.

> A user can generate (public key, secret key) pair as he needs, without needing to ask anyone (CA) to certificate the binding between his public key and his real identity. (Anonymity, decentralization)

* Privacy in Bitcoin: Each user can generate an arbitrary number of (public key, secret key) pair as he needs; Ideally, each (public key, secret key) pair is used only one time. 3 ways to enhance the privacy:

Hide the source of the transfer; Hide the destination of the transfer; Hide the amount

* Using Hash as the Address: Each TXO is an **(address, value)** pair, where address is the hash of the payee’s public key / a hash value of something.

For a transfer transaction, the payee does not need to send his public key to the payer, instead, only needs to send a hash value to the payer.

==The hash value can be the hash of anything, e.g., a public key, a script describing some conditions, or just a
meaningless string==

### Transaction of Bitcoin

```json
{
  "hash": "5a42590fbe0a90ee8e8747244d6c84f0db1a3a24e8f1b95b10c9e050990b86b6", 
    // Unique identifier of the transaction, obtained by hashing the transaction data
  "ver": 1, 
    // Version of the transaction format (1 is the original version)
  "vin_sz": 2, 
    // Number of input transactions (vin stands for "value in")
  "vout_sz": 1, 
    // Number of output transactions (vout stands for "value out")
  "lock_time": 0, 
    // Block number or timestamp until which the transaction is locked (0 means no lock)
  "size": 404, 
    // Size of the transaction in bytes
  "in": [ // List of transaction inputs
    {
      "prev_out": { // Details of the previous transaction output being spent
        "hash": "3be4ac9728a0823cf5e2deb2e86fc0db2aa503a91d307b42ba76117d79280260", 
          // Hash of the previous transaction
        "n": 0 
          // Index of the specific output in the previous transaction to be spent
      },
      "scriptSig": "304402...AC" 
          // Signature script that provides the necessary signatures and public keys to spend the input
    },
    {
      "prev_out": {
        "hash": "7508e6ab259b4df0d5147babc0948d1473db4518f81afc5c3f52f91ff6b34e", 
          // Another previous transaction hash
        "n": 0 
          // Another output index from a different previous transaction
      },
      "scriptSig": "3f34ace81...BC" 
        // Another signature script for the second input
    }
  ],
  "out": [ // List of transaction outputs
    {
      "value": "10.12278097", // Amount of bitcoins being sent in this output
      "scriptPubKey": "OP_DUP OP_HASH160 69e02e18b5750a5d6db28ed51771c6894b3d42e OP_EQUALVERIFY OP_CHECKSIG" 
        // Locking script that specifies the condition to spend this output, typically a hashed public key or a Bitcoin address
    }
  ]
}

```

* Each input includes :

(1) a reference to existing TXO (i.e., some output of some previous transaction);
(2) A proof that the spending (of that TXO) is authorized

* Each output includes : 

(1) a value; (2) an address (script)

* A transaction is valid, only if

1. The transaction output (TXO) referenced by each input is not referenced by other previous transactions (i.e. not double spending)
2. The public key and signature provided in each input is verified valid (with respect to the referenced TXO’s address) (i.e. authorized and authenticated)

3. The total value of outputs is not greater than that of the input coins（the difference will be the transaction fee）(i.e. not over spending)

### Script of Bitcoin

**"in"->scriptSig**: The **signature** and **public key** in each input

**"out"->ScriptPubKey**: The address in TXO contains a script source code containing opcodes and operands

The **scriptSig** of an input will be put together with the **scriptPubKey** of the TXO it references, running the opcodes on the operands to check the validify of the spending.

![image-20231224232654240](C:\Users\NP_123\AppData\Roaming\Typora\typora-user-images\image-20231224232654240.png)

Later, when the receiver wants redeem these coins, he needs to reveal the script that has the given hash, and provides data that will make the script evaluate to true.



### Block of Bitcoin

* Merkle Tree

  1. A binary tree built with **Hash pointers**
  2. Allows a concise proof of membership
  3. Allows a quick check on whether the data in the set are tampered

  **Tamper-resistance:** Any modification of a data block will incurs the change of the hash values on the path from the leaf node to the root node.

  **Proof of membership:** 1) a data block. 2) the nodes on the path from the data block to the root.

  Time/Space Complexity: $O(\text{log}n)$

Transactions are organized into a Merkle Tree, the hash of the Merkle Tree Root is contained in Block Header, and the block  headers are chained by hash pointers --- forming Block-Chain.

* Hash Pointer: Given a hash value ℎ𝑣𝑎𝑙, use ℎ𝑣𝑎𝑙 as the identifier for records and fetch the data DATA from the database, then check whether ℎ𝑣𝑎𝑙 = 𝐻(𝐷𝐴𝑇𝐴) holds. Only if it holds, the fetched DATA is correct.
* Hash Chain:  Contains **only hash of the block header.** $$prev_i=H(Block_{i-1})=H(prev_{i-1}||Data_{i-1})$$

* Block header: containing the hash of previous block header, and the hash of Merkle tree root node.

| FIeld             | size   | Description                              |
| ----------------- | ------ | ---------------------------------------- |
| previousblockhash | 32Byte | Hash of the previous block               |
| merkleroot        | 32Byte | Hash of Merkle Tree for the transactions |
| difficulty        | 4Byte  | Difficulty for mining                    |
| nonce             | 4Byte  | Nonce                                    |

> Q: The hash of the block is not included in the block itself, neither transmitting on network or storing
> as a part of the block in storage. why?
>
> A: 1.Since the hash is a result of the block's data, including the hash within the block itself would be a logical impossibility. 2. By referencing the previous block's hash in each new block, a secure link is formed.

* Coinbase transaction: One input, and one output; Does not consume any coins; 

Output value = current block reward + transaction fee

"coinbase" field: the miner can put any information in this parameter.

>  Q: **Note that there is not signature to guarantee that the coinbase transaction’s integrity. Could an attacker modify other’s coinbase transaction to get the block reward and transaction fee?**
>
> A: **The integrity of the coinbase transaction, like all transactions in a block, is protected by the block's hash and the Proof of Work system.** 



### Mining

1. Set the value of the nonce in the block header, then compute the hash value of the block header. If it is smaller than the target, a valid block candidate is found, otherwise, change the nonce, and try again.
2. There are $2^{32}$ values for Nonce. If no valid block candidate is found even after all $2^{32}$ values for Nonce have been tried, a miner can modify the coinbase parameter in the coinbase transaction, so that the hash value of Merkle tree root changes, then search again in the scope of nonce.

* Mining is to repeatedly run the hash algorithm on block header, until a hash value smaller than the target is found.
* The difficulty will be adjusted each 2016 blocks are generated.

* More (computing) resource to mine, more possible to be a winner.



### Bitcoin Network

A peer-to-peer network; all nodes are equal; runs over TCP and has a random topology; The network changes over time and is quite dynamic due to nodes entering and leaving.

1. When a user/node issues a transaction, it broadcasts the transaction to its peers.
2. When a node receives a transaction, it executes the flooding algorithm.

Check the validity of the transaction(using local blockchain):{

​		Check whether there is double-spending **By maintain a local UTXO list** 

​		Check the balance of input and out coin value

​		Check whether the transaction is authorized **By checking whether each scriptSig and the corresponding scriptPubKey returns TRUE**

}

Check whether this transaction have been received and in the pool

3. Mining: Miner uses the latest block in the current local blockchain as the previous block node, selects a set of transactions from its transaction pool, constructs the corresponding coinbase transaction, and constructs Merkle Tree of these transactions, then, begin to mine: **compute hash by combining previousblockhash, merkle tree root, and different nonce. If necessary, change the coinbase parameter in the coinbase transaction.**
4. Some miner finds a valid block candidate, then broadcasts the block candidate to the Bitcoin Network.
5. When a node receives a new candidate block, it runs the flooding algorithm

* race condition: the nodes will temporarily disagree on which transactions should be put into the next block. This race condition is solved when miners finds new block.

* Default policy of Bitcoin protocol:

1. When a node receives multiple conflicting transactions, it will keep the one received first, and ‘discard’ others.
2. When the received new blocks make the local blockchain fork, if the blockchain forks have the same length, the node will select the one received first. Otherwise, the node will select the longest chain fork.

### Bitcoin Consensus

* **Data stored in fully validating nodes(mine):**

1. Complete Blockchain (headers, transactions)
2. List of UTXO (To proceed the transactions quickly)
3. Transaction Pool (select transactions and mine)

* **Data stored in lightweight nodes (Simplified Payment Verification (SPV) Clients, do not mine):**

1. Complete chain of the block headers.
2. Pieces that they need to verify specific transactions that they care about

* **Target of consensus:** At any moment, all nodes in the Bitcoin Network agree on a series of blocks and the transactions in these blocks.

* Why does a node behave honestly? Once the proposed block is accepted by whole network, the miner
  will obtain the block reward and transaction fee.

* **Why follow/choose the longest chain?** Each block implies corresponding computation power has been invested on the block. Longer chain implies more computation power accepting the chain, and implies bigger probability these blocks are accepted by the consensus blockchain. And the blocks not on the longest chain will be “discarded” (not accepted by the nodes). ==So even the blocks on chain may be discarded later.==

* when do the blocks achieve finality/stability and become one part of the consensus blockchain? ==6== 

### Mining Pools

**Pool Manager** prepares the block to mine, does very thing except computing hash. **Pool Members** only computes hash to find the right nonce.

The pool manager will distribute the fees to all the pool members based on how much work each member actually performed.

* **Pay models:**

1. Pay-per-share: Pool manager pays a flat fee for every share, without waiting for the pool to find a block.
   The pool manager absorbs all of the risk.
2. Proportional: The amount of payment depends on whether or not the pool actually found a valid block.

* **A weakness of Mining Pool:** there is nothing to enforce that the member miners actually submit valid blocks to the pool manager in the event that they find them.

* Pros and Cons of Mining Pools:

1. Pros: Make mining much more predictable for the participants and make it easier for small miners to get involved in the game; Make it easier to update the network
2. Cons: Mining pools are a form of centralization; Lower the number of fully validating nodes; Make some attacks easier

* **Non-outsourceable mining:** make the miners who search the nonce have to know the secret key for the coinbase transaction.



### Attacks(Both result Double-Spending)

* Forking Attacks(51%) : A malicious miner sends coins by a transaction to Bob and receives some goods or service in exchange for it. The miner then forks the block chain to create a longer branch containing conflicting transaction. The payment to Bob will be invalid in this new consensus chain. (control 51% computation power or creating a new mining pool)
*  Selfish Mining: Say that a miner just found a block, it does not announce it right away as the default/honest protocol requires. Instead, it tries to get ahead by doing some more mining on top of this block in hopes of finding two blocks in a row before the rest of network finds even one, keeping its
  blocks secret the whole time; Once a new block by other miners is announced, the attacker immediately announces its two blocks in a row, so that its blocks make a longer chain.

### Bitcoin Scripts

* **MULTISIG transaction:** requires two of three people to sign in order to redeem the coins.

* **Efficient micro-payment:** Alice sets up a MULTISIG escrow transaction on the blockchain, prepaying the maximum amount she might need for Bob's service. For each minute of service used, Alice signs a new transaction allocating a small payment to Bob and returning the rest to herself. These transactions are not yet signed by Bob or broadcasted to the blockchain. Once the service period ends, Alice stops creating new transactions. Bob then signs and publishes the final transaction Alice sent, which pays him for the total service provided and refunds any remaining amount to Alice. The intermediate transactions Alice signed are discarded as they are never completed and published on the blockchain.

<img src="C:\Users\NP_123\AppData\Roaming\Typora\typora-user-images\image-20231227063054463.png" alt="image-20231227063054463" style="zoom:80%;" />

==Problem: what if Bob never signs the last transaction? He may just say, “I’m happy to let the coins sit there in escrow forever,” in which case, maybe the coins won’t move, but Alice will lose the full value that she paid at the beginning. Introduce Lock Time.==

* Lock Time: Before publishing this ESCROW transaction, Alice asks Bob to sign a REFUND transaction which refunds all of Alice’s money back to her, but the refund is “locked” until some time in the future. Alice also signs this refund transaction and hold on to it. Then Alice publish the ESCROW transaction to
  the blockchain.

<img src="C:\Users\NP_123\AppData\Roaming\Typora\typora-user-images\image-20231227063123731.png" alt="image-20231227063123731" style="zoom:80%;" />

If Bob does not sign a transaction to redeem pays for his service before the refund transaction becomes valid, all the escrowed amount will be sent back to Alice.
If Bob honestly signs a transaction to redeem pays to him, the refund transaction will become a double-spending transaction, and miners will discarded it.



### Wallet

A software or hardware that stores and manages the keys for the owner

* Hot Storage: On-line and Internet-connected storage, Convenient, but may be insecure, like cash in wallet

The addresses and secret keys in hot storage are used frequently to receive coins and spend coins.

When the number of coins on a hot address is big, you can spend the coins to some cold address.

* Cold Storage: Off-line storage, locked somewhere. Safe, but not convenient

To have better privacy, each cold address is used only once, i.e. appearing in only one transaction as receiving address



### Hierarchical Deterministic Wallet

* Master Public Key Property: the public keys can be derived from a master public key, without needing the (master) secret key(s)

* Hierarchy Property: Each (public key, secret key) pair can act as the master key for its sub-organization.

<img src="C:\Users\NP_123\AppData\Roaming\Typora\typora-user-images\image-20231227195942401.png" alt="image-20231227195942401" style="zoom:80%;" />

​	

* Applications of Deterministic Wallet

1. Low-maintenance wallets with easy backup and recovery: Only need to back up the master secret key
2. Freshly generated cold addresses: Store the master public key on hot storage, then can easily and conveniently generate cold addresses
3. Trustless audit: Reveal the master public key to the auditors, then the auditors can view all the
   transactions related to the wallet
4. Hierarchical Wallet allowing a treasurer to allocate funds to departments

* How to store and protect the master secret key? ==Brain Wallet; Paper Wallet==

* Online Wallet: the site delivers the code that runs on your browser or the app, and it also stores your keys.
* Exchanges: Buying or selling coins at the exchange will not have transactions on the blockchain.
  When a user withdraws coins from an exchange, a corresponding transaction appears on the blockchain.





