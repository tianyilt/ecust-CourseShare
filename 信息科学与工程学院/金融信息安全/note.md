

### GCD(a,b)

```go
func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}
```

### Extended Euclidean Algorithm

$$ax + by = \text{gcd}(a, b)$$

Def: A is the modular inverse of B mod n if AB mod n = 1.

There exists a modular inverse for B mod n iff B is relatively prime to n. ( $$\text{gcb}(b,n) = 1$$ )

### Euler's Function

$$\phi(n)=n(1-1/p_1)(1-1/p_2)\cdots(1-1/p_k)$$

1.  The Euler phi function is multiplicative. I.e. if $$\text{gcd}(m, n) = 1$$, then $$\phi(mn) = \phi(m) \times \phi(n)$$.

2.  For a prime p and an integer $e\geq 1$, $$\phi(p^e) = p^{e-1}(p-1)$$.

* ==if a and n are co-prime, then $a^k\text{ mod }n=a^{k\text{ mod }\phi(n)}\text{ mod } n$==

### Fermat’s Little Theorem

Let $$p$$ be a prime. Any integer $$a$$ not divisible by $$p$$ satisfies $$a^{p-1}\equiv 1 (\text{mod }p)$$.

* Compute $$11^{1,073,741,823} \text{ mod } 13$$.

let $$p=13$$,     $$13\text{ mod }11\neq 0$$, So:

​			$$11^{13-1=12}\equiv1(\text{mod }13)$$

Raise both sides to a large power. First, find that power: $$\frac{1,073,741,823}{12}=89478485 \cdots \cdots3$$

​			$${(11^{12})}^{89478485}\equiv1^{89478485}(\text{mod }13)$$

​			$$11^{1073741820}\equiv1(\text{mod }13)$$

​			$$11^{3}\times 11^{1073741820}\equiv11^{3}(\text{mod }13)\equiv1331(\text{mod }13)\equiv5(\text{mod }13)$$

​			$$11^{1,073,741,823} \text{ mod } 13=5$$

### Modular exponentiation

1. Repeated Modular Multiplication (as defined)

$$a^e\text{ mod }n$$ is defined as repeated multiplications of a for $$e$$ times modulo n; Complexity = $$O(e)$$

2. Square-and-Multiply Algorithm

$$11^{15}\text{ mod }13=11^8 \times 11^4\times 11^2\times 11 \text{ mod }13$$,  Complexity = $$O(|e|)\text{ or } O(\text{lg}(e))$$

```go
func modularExp(a, e, n int) int {
	z := 1
	for i := e; i > 0; i /= 2 {
		if i%2 != 0 {
			z = (z * a) % n
		}
		a = (a * a) % n
	}
	return z
}
```

==**Determine whether 227 and 79 are relatively prime.**==

gcd(227,79)=gcd(79,69)=gcd(69,10)=gcd(10,9)=1    So they are relatively prime.

==**Find the multiplicative inverse of 79 mod 229.**==

Like Q1, gcd(79,229)=1. 

229=79 x 2+71

79=71+8

71=8 x 8 +7

8=7+1

reverse 1 into the form: ax + by

1=8-7=8-(71-8x8)=9x8-71=9x(79-71)-71=9x79-10x71=9x79-10x(229-79x2)=29x79-10x229

$$1 \text{ mod }229=1=29\times79\text{ mod }229$$

29 is the modular inverse of 79 modulo 229.

##### ==**Without calculating anything, by simply looking at the numbers, can you tell whether 7932 has a multiplicative inverse mod 11958? Explain.**==

No. because they are not relativity prime since they can all divided by 2.

==**Show the steps of how to calculate $$\phi(730)$$.**==

$$730=2\times5\times73$$

$$\phi(730)=1\times4\times72=228$$

==**Calculate $$227^{54996213}\text{ mod }21$$ as efficient as possible.**==

227 and 21 are co-prime

$a^k\text{ mod }n=a^{k\text{ mod }\phi(n)}\text{ mod } n$

$227^{54996213}\mod 21=227^{54996213\mod \phi(21)}\mod 21=227^{9}\equiv17^9\mod 21\equiv 20$

### Abelian group

* Abelian Group Definition 

1. **Closure**: For all elements $$a, b$$ in the group, the result of $$a*b$$ must also be in the group.
2. **Associativity**: For all elements $$a, b,$$ and $$c$$ in the group, $$(a*b)*c = a*(b*c)$$.

3. **Identity Element**: There exists an element $$e$$ in the group such that for every element $$a$$ in the group, $$a*e = e*a = a$$.

4. **Inverse Element**: For each element $$a$$ in the group, there exists an element $$b$$ in the group such that $$a*b = b*a = e$$, where $$e$$ is the identity element.

5. **Commutativity**: For all elements $$a, b$$ in the group, $$a*b = b*a$$.

e.g: {1,2,3,4} with operator * (mod 5) is an abelian group. However, {0,1,2,3} is not

* Multiplicative Groups    $$ \mathbb{Z}_n^* = \{a \in \mathbb{Z}_n | \gcd(a, n) = 1\} $$

* Cyclic Groups

If there is an element $$g\in G$$, for each $$a\in G$$, there is an integer i with $$a=g^i$$, that is g operates on it self for i times. -> genrator: g

e.g: ($$Z_7^*,x$$) is a cyclic multiplicative group with g=3

| i                     | 1    | 2    | 3    | 4    | 5    | 6    |
| --------------------- | ---- | ---- | ---- | ---- | ---- | ---- |
| $$g^i \text{ mod }7$$ | 3    | 2    | 6    | 4    | 5    | 1    |

$$
\mathbb{Z}_n^* \text{ has a (at least one) generator if and only if } n = 2, 4, p^k, \text{ or } 2p^k,
$$

where \( $$p$$ \) is an odd prime and \( $$k \geq 1$$ \).

==**is $$(\mathbb{Z}_5, +)$$ cyclic? give a genrator of the group **==

The element $$1$$ generates the group as $$1 + 1 = 2$$, $$2 + 1 = 3$$, $$3 + 1 = 4$$, $$4 + 1 = 0$$ (all modulo 5).

Similarly, the element $$2$$ generates the group as $$2 + 2 = 4$$, $$4 + 2 = 1$$, $$1 + 2 = 3$$, $$3 + 2 = 0$$ (all modulo 5).

Hence, the generators for $$(\mathbb{Z}_5, +)$$ are $$\{1, 2, 3, 4\}$$.

==**is $$(\mathbb{Z}_8^*, \times )$$ cyclic? give a genrator of the group **==

The elements of $$( \mathbb{Z}_8^* )$$ are $$\{1, 3, 5, 7\}$$. To check for cyclicity:

   - The element $$1$$ is not a generator since $$1 \times 1 = 1$$.
   - The element $$3$$ is not a generator because $$3^2 = 9 \equiv 1 \mod 8$$, and it does not generate all elements.
   - The element $$5$$ is not a generator because $$5^2 = 25 \equiv 1 \mod 8$$, and it also does not generate all elements.
   - The element $$7$$ is not a generator because $$7^2 = 49 \equiv 1 \mod 8$$, and it fails to generate all elements.

   Since none of the elements generate the entire group, \( (\mathbb{Z}_8^*, \times) \) is not cyclic.

==**is $$\mathbb{Z}_6^*$$ forms a cyclic group？**==

$$ \mathbb{Z}_6^* = \{a \in \mathbb{Z}_6 | \gcd(a, 6) = 1\} = \{1, 5\} $$

- $$ 5^1 \equiv 5 \mod 6 $$
- $$ 5^2 \equiv 25 \equiv 1 \mod 6 $$

$$ \mathbb{Z}_6^* \text{ is cyclic with 5 as a generator.} $$

### Generate Primes

* Security Parameter: Security parameter is an integer value (denoted by n ) that parameterizes both cryptographic schemes as well as all involved parties
* Efficient Algorithms: There is some polynomial such that the algorithm runs for time at most $p(n)$ when the security parameter is $n$.
* Negligible Probability: **“small probabilities” with probabilities smaller than any inverse polynomial in n. Such probabilities are called negligible.**

$$f: \mathbb{Z}^+ \rightarrow \{0\} \cup \mathbb{R}^+$$ is negligible , if for every positive polynomial $p$ and all sufficiently large values of $n$ it holds that $f(n) < \frac{1}{p(n)}$.

E.g: $f(n) = 2^{-n}$ is a negligible function.

```go
func generateRandomPrime(n int) (int, error) {
	if n >= 31 { // 31-bit is the practical limit for a signed int
		return 0, fmt.Errorf("bit length too large for int type")
	}

	var p int
	max := 1 << n       // 2^n
	min := 1 << (n - 1) // Ensure n-bit length

	rand.Seed(time.Now().UnixNano())

	for i := 0; i < 3*n*n; i++ {
		p = rand.Intn(max-min) + min
		p |= 1 // Ensure p is odd

		if isProbablyPrime(p, n) {
			return p, nil
		}
	}

	return 0, fmt.Errorf("failed to generate a prime number")
}
```

### Cryptographic Hardness Assuptions

* **Gengroup:** A generic, polynomial-time, group-generation algorithm that, on input $1^n$, outputs a description of a cyclic $G$, its order $q$, and a generator $g\in G$.

* **Discrete Logarithm:** Let $G$ be a cyclic group, for every $h\in G$, there is a unique $x\in Z_q$ such that $h=g^x$ and this $x$ is called the discrete logarithm of $h$ with respect to $g$, written as $x=\text{log}_gh$.

$\text{Pr}[\text{DLog}_\text{GenGroup,A}(n)=1]\leq negl(n)$

* **Discrete-logarithm (DL) Problem:** Given the $(G,q,g)\leftarrow \text{GenGroup}(1^n)$ and a uniform $h\in G$, find $x\in Z_q$ such that $h=g^{x}$.

* **Computational Diffie-Hellman Problem:** Given the $(G,q,g)\leftarrow \text{GenGroup}(1^n)$ and uniform elements $h_1,h_2\in G$, find $h\in G$ such that $h=g^{x_1x_2}$ where $x_1=\text{log}_gh_1, x_2=\text{log}_gh_2$.

* **Decisional Diffie-Hellman Problem:** Given the $(G,q,g)\leftarrow \text{GenGroup}(1^n)$ and uniform elements $h_1,h_2\in G$, and an element $T\in G$. Determine whether $T=g^{x_1x_2}$ holds, where $x_1=\text{log}_gh_1, x_2=\text{log}_gh_2$.



### Public Key Encryption

* Syntax: $\text{KeyGen}(\lambda)\to (pk,sk)$,  $\text{Enc}(pk,m)\to c$, $\text{Dec}(sk,c)\to m$

* Kerckhoffs’ Principle: Cryptographic designs should be made completely public; Only the key is secret.

* Security guarantee: **defines what the scheme is intended to prevent the attacker from doing**

❌ It should be impossible for an attacker to recover the key. 

❌ It should be impossible for an attacker to recover the **entire plaintext** from the ciphertext.

❌ It should be impossible for an attacker to recover **any character** of the plaintext from the ciphertext.

✅ regardless of any information an attacker already has, a ciphertext should leak ==no additional information== about the underling plaintext.

e.g: Let's say an attacker knows that a message being sent every day at a specific time is either "The stock price is up" or "The stock price is down", and nothing else. If the encryption scheme is semantically secure, then the attacker, upon intercepting the encrypted message, would gain no additional information about which of the two possible messages was sent on any given day.

* The threat model: **describes the power of the adversary, i.e., what actions the attacker is assumed able to carry out.**

1. Ciphertext-only attack
2. Known-plaintext attack
3. Chosen-plaintext attack **(CPA)**
4. Chosen-Ciphertext attack **(CCA, strongest)**

Strong: CCA>CPA>KPA>COA

* El Gammal Encryption:

$KeyGen(1^\lambda)\to(pk,sk)$, choose a random $x\in Z_q$ and computes $h:=g^x$.

$pk:=(G,q,g,h)$, $sk:=(x)$

$Enc(pk,m)\to c$ ; ciphertext $(c_1,c_2):=(g^y,m \times h^y )$.

 $Dec(sk,c)\to m$ ; $m:=c_2/c_1^x=\frac{m\times h^y}{g^{xy}}=\frac{m\times h^y}{h^y}=m$

If the DDH problem is hard relative to $GenGroup$, then the El Gamal Encryption scheme is CPA-secure. However, it is not CCA-Secure.

### Digital Signature

* Correctness: It is required that except with negligible probability over $(pk,sk)$ output by $KeyGen()$, it holds that $Verify(pk,m,Sign(sk,m))=1$ for every message $m\in M$.
* Features: Public Verifiability; Transferability; Non-repudiation

### Hash Function

Syntax: polynomial-time algorithm $H:\{0,1\}^{*}\to\{0,1\}^{l(n)}$ that takes as input a string $x\in \{0,1\}^{*}$ and outputs a string $H(x)\in \{0,1\}^{l(n)}$

* Collision-Resistance: no efficient adversary can find a collision except with non-negligible probability.

$Pr[\text{HashColl}_{A,H}(n)=1]\leq\text{negl}(n)$

For Adversay A: 1. A is given H and n. 2. A outputs two strings $x,x^{'}\in\{0,1\}^*$.

The output of the experiment is defined to be 1 if and only if $x\neq x^{'}$ and $H(x)=H(x^{'})$.

* Second-preimage or target-collision resistance: Given a uniform $x\in \{0,1\}^{*}$ it is **infeasible** for a PPT adversary to find $x^{'}\neq x $ and $H(x^{'})=H(x)$
* Preimage resistance: given a uniform $y\in \{0,1\}^{l(n)}$ it is infeasible for a PPT adversary to find a value $x\in \{0,1\}^*$ such that $H(x)=y$.

Hardness: Preimage > Second-preimage > Collision

> MD5: 128 bit output, MD5 collisions found (easily)
>
> SHA-1: 160 bit output, collision found in 2017, new progress was made in 2019
>
> SHA-2 (SHA 256): longer hash value



### Hybrid Encryption

| Symmetric Key Encryption (SKE)<br />(Secret key encryption scheme) | Public key Encryption (PKE)<br />Public key encryption scheme |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Two parties MUST trust each other                            | **Two parties DO NOT need to trust each other**              |
| Both share the same key (or one key is computable from the other) | Two separate keys: a public and a private key                |
| Attack approach: bruteforce                                  | Attack approach: solving mathematical problems (e.g. factorization, discrete log problem) |
| **Faster**                                                   | Slower (100-1000 times slower)                               |
| Smaller key size                                             | Larger key size                                              |
| Has major problem in key distribution.                       | No key distribution problem.                                 |

* Hybrid encryption scheme uses: Public key encryption to avoid key distribution problem. Secret key encryption to do bulk encrypting for efficiency.

1. choosing a uniform value $k$.
2. encrypting $k$ using a public-key encryption scheme.

### Certification Authority (CA)

> Sender has to be sure that the public key used for encryption is indeed the receiver’s public key -> CA
>
> Verifier has to be sure that the public key used for signature verification is indeed the signer’s public key

CA has a public key which is ASSUMED to be well known. The certification bears:

==1.The public key owner's identity. 2. the public key. 3. A validity period of the certificate and 4. the CA's signature.==

$\text{Cert}_A=(\text{ID}_A,\text{PK}_A,\text{expiry-date},\text{Sign}_{CA}(	\text{ID}_A,\text{PK}_A,\text{expiry-date}))$



### Diffie-Hellman Key Exchange

<img src="C:\Users\NP_123\AppData\Roaming\Typora\typora-user-images\image-20231228213442157.png" alt="image-20231228213442157" style="zoom:67%;" />

Alice computes $(g^b)^a=g^{ba}=g^{ab} \text{ mod }p $. Bob computes $(g^a)^b=g^{ab} \text{ mod }p $.

Could use $K=g^{ab}\text{ mod }p$ as symmetric key

could agasint **eavesdroppers**, insecure in **man-in-the-middle attack**.





### 考点总结：第一章

比特币的介绍，笼统，没有细节。

区块链应用，都是宏观，考概念。不考综合。 基础题占50%-60% 两个大题一半一半

### 第二章(大块头)

考一些基础性的题目，指数取模（可能出计算）。ppt仔细去看，练习要会做

* 哈希函数基本定义（什么样的函数是？满足什么样的性质-才能在密码学里使用？安全模型？攻击者模型？定义安全性？满足什么情况的时候是安全的？抗碰撞性是怎么定义的？ 不止要自然语言，也要数学语言(PKE)
* 可忽略函数的含义？某个概率可忽略？

### 比特币

账本-怎么设定、交易-结构、基本原理、基本构造、基本安全性的性质、比特币脚本、挖矿的原理-难度-参数、攻击、安全性分析-多长是安全的-双挖、**比特币钱包**、确定性的分层的算法(**算法要重点学，密码学基础之上，与金融密切相关，考核很重要的点**)

PBFT 宏观脉络，协议是干什么的

比特币的隐私概念、Coin-mix-coin shuffle基本的概念(知道基本概念、原理就行，不详细)

不要知道细节，知道干什么的就行了 ，基本语法

development、匿名性、怎么定义的  攻击模型的脉络

### 门罗币必考：

比较复杂的协议，不需要背所有细节。宏观的粗粒度的就可以了

解释一下门罗币的接收者的隐藏策略

解释下基本原理

协议构造

