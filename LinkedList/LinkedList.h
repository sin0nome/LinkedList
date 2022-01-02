#ifndef __LINKEDLIST_H__
# define __LINKEDLIST_H__

namespace List{
	// primary template
	template <class T1>
	class LinkedList{
	private:
		template <class T1>
		class Node{
		public:
			T1 value;		// 格納されている値
			Node *prev;		// 前のノード
			Node *next;		// 次のノード
		};

		Node<T1> *nullptrKUN;		// ぬるぽ君(番兵)NullPointerではない

		// valを持つ最初のノードのポインタを返す
		Node<T1> *listSearch(const T1 value){
			Node<T1> *current = nullptrKUN->next;	// 次のノードを現在のノードとして扱う
			// 次のノードが現在と同じアドレスの場合はそれ以降存在しないのでループ終了
			// 引数の値が出現するまで前から順に検索していく
			while(current != nullptrKUN && current->value != value){
				current = current->next;			// 次のノードへ
			}
			return current;
		};

		// 引数に与えられたノードを削除
		void deleteNode(Node<T1> *node){
			if(node == nullptrKUN){
				return;  // nodeが番兵の時は何もしない
			}
			// リンクつなぎ変え
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;  // メモリ解放
		};

	public:
		// constructor
		LinkedList(){
			this->nullptrKUN = new Node<T1>;
			this->nullptrKUN->next = this->nullptrKUN;		// 番兵のノードアドレスを代入
			this->nullptrKUN->prev = this->nullptrKUN;		// 番兵のノードアドレスを代入
			this->nullptrKUN->value = 0;					// 初期値として0を代入
		};

		// 先頭に追加
		void addFirst(const T1 value){
			Node<T1> *newNode = new Node<T1>;			// ノードの新規作成
			newNode->value = value;						// 新規作成したノードに値の代入

			// リンクのつなぎ替え(ノード0とノード1の間に挟みこむ感じ.ノード0はnullprtKUN)
			newNode->next = this->nullptrKUN->next;		// 新規作成したノードの次ノード先として現在のノードの次ノードアドレスを代入
			newNode->prev = this->nullptrKUN;			// 新規作成したノードの前ノード先として現在のsノードアドレスを代入
			this->nullptrKUN->next->prev = newNode;		// 現在のノードの次ノードの前ノードとしてに新規作成したノードアドレスを代入
			this->nullptrKUN->next = newNode;			// 現在のノードの次ノードとして新規作成したノードアドレスを代入
		};

		// 末尾に追加
		void addLast(const T1 value){
			Node<T1> *newNode = new Node<T1>;			// ノード新規追加
			newNode->value = value;						// 値の代入

			// リンクの繋ぎ変え(addFirstとやることはほぼ同じ)
			newNode->prev = this->nullptrKUN->prev;		// 新規作成ノードの前ノードに番兵の前ノードを設定
			newNode->next = this->nullptrKUN;			// 新規作成ノードの次ノードに番兵を設定
			this->nullptrKUN->prev->next = newNode;		// 番兵の前ノードの次ノードを新規作成したノードに設定
			this->nullptrKUN->prev = newNode;			// 番兵の前ノードを新規作成したノードに設定
		};

		// valを持つ最初のノードを削除
		void deleteValue(const T1 value){
			deleteNode(listSearch(value));
		};

		// 先頭のノードを削除
		void deleteFirst(){
			deleteNode(nullptrKUN->next);
		};

		// 末尾のノードを削除
		void deleteLast(){
			deleteNode(nullptrKUN->prev);
		};

		// 末尾から指定数番目ノードの内のvalを書き換える(存在しないノードを指定した場合はfalseを返す)
		bool updateLast(const T1 val, const int nodeNum){
			Node<T1> *current = this->nullptrKUN->prev;
			for(int i = 0; i < nodeNum; i++){
				if(current == this->nullptrKUN){
					return false;					// 存在しないノードを指定した場合はfalseを返す(何もしない)
				}
				current = current->prev;			// 後ろへ
			}
			current->value = val;					// 上書き
			return true;
		};

		// 先頭から指定数番目ノードの内のvalを書き換える(存在しないノードを指定した場合はfalseを返す)
		bool updateFirst(const T1 val, const int nodeNum){
			Node<T1> *current = this->nullptrKUN->next;
			for(int i = 0; i < nodeNum; i++){
				if(current == this->nullptrKUN){
					return false;					// 存在しないノードを指定した場合はfalseを返す(何もしない)
				}
				current = current->next;			// 前へ
			}
			current->value = val;					// 上書き
			return true;
		};

		// 先頭ノードのvalを取得
		T1 getValueNodeFirst() const{
			return this->nullptrKUN->next->value;
		};

		// 末尾ノードのvalを取得
		T1 getValueNodeLast() const{
			return this->nullptrKUN->prev->value;
		};

		// 先頭から指定数番目のvalを取得。存在しないノードを指定した場合,型最大まで1で埋めた値を返す
		T1 getValueSelectNodeFirst(const int nodeNum) const{
			Node *current = nullptrKUN->next;		// 次のノードを現在のノードとして扱う
			T1 val = nullptrKUN->value;				// 保存用
			val = current->value;					// 現ノードの値を代入
			// 指定番号のノードまで前から検索
			for(int cnt = 0; cnt < nodeNum; cnt++){
				current = current->next;			// 次のノードへ

				// 前回の値(ポインタ)と同じ場合はそれ以降は存在しないので探索終了
				// 存在しない場合は0を返す
				if(nullptrKUN == current){
					return  0;
				}
				val = current->value;				// 現ノードの値を代入
			}
			return val;
		};

		// 末尾から指定数番目のvalを取得。存在しないノードを指定した場合,型最大まで1で埋めた値を返す
		T1 getValueSelectNodeLast(const int nodeNum) const{
			Node<T1> *current = nullptrKUN->prev;	// 次のノードを現在のノードとして扱う
			T1 val = nullptrKUN->value;				// 保存用
			val = current->value;					// 現ノードの値を代入
			// 指定番号のノードまで前から検索
			for(int cnt = 0; cnt < nodeNum; cnt++){
				current = current->prev;			// 前のノードへ

				// 前回の値(ポインタ)と同じ場合はそれ以降は存在しないので探索終了
				// 存在しない場合は0を返す
				if(nullptrKUN == current){
					return 0;
				}
				val = current->value;				// 現ノードの値を代入
			}
			return val;
		};

	};


	/* ======== T1がポインタ型の場合 ======== */

	// 部分特殊化
	template<class T1>
	class LinkedList<T1*>{
	private:
		template<class T1>
		class Node{
		public:
			T1 value;		// 格納されている値
			Node *prev;		// 前のノード
			Node *next;		// 次のノード
		};

		Node<T1*> *nullptrKUN;		// ぬるぽ君(番兵)NullPointerではない

		// valを持つ最初のノードのポインタを返す
		Node<T1*> *listSearch(const T1* value){
			Node<T1*> *current = nullptrKUN->next;	// 次のノードを現在のノードとして扱う
			// 次のノードが現在と同じアドレスの場合はそれ以降存在しないのでループ終了
			// 引数の値が出現するまで前から順に検索していく
			while(current != nullptrKUN && current->value != value){
				current = current->next;			// 次のノードへ
			}
			return current;
		}

		// 引数に与えられたノードを削除
		void deleteNode(Node<T1*> *node){
			if(node == nullptrKUN){
				return;		// nodeが番兵の時は何もしない
			}
			// リンクつなぎ変え
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;	// メモリ解放
		}

	public:
		// constructor
		LinkedList(){
			this->nullptrKUN = new Node<T1*>;
			this->nullptrKUN->next = this->nullptrKUN;		// 番兵のノードアドレスを代入
			this->nullptrKUN->prev = this->nullptrKUN;		// 番兵のノードアドレスを代入
			this->nullptrKUN->value = nullptr;				// 初期値としてnullprtを代入
		}

		// 先頭に追加
		void addFirst(const T1 *value){
			Node<T1*> *newNode = new Node<T1*>;			// ノードの新規作成
			newNode->value = (T1*)value;				// 新規作成したノードに値の代入

			// リンクのつなぎ替え(ノード0とノード1の間に挟みこむ感じ.ノード0はnullprtKUN)
			newNode->next = this->nullptrKUN->next;		// 新規作成したノードの次ノード先として現在のノードの次ノードアドレスを代入
			newNode->prev = this->nullptrKUN;			// 新規作成したノードの前ノード先として現在のsノードアドレスを代入
			this->nullptrKUN->next->prev = newNode;		// 現在のノードの次ノードの前ノードとしてに新規作成したノードアドレスを代入
			this->nullptrKUN->next = newNode;			// 現在のノードの次ノードとして新規作成したノードアドレスを代入
		}

		// 末尾に追加
		void addLast(const T1 *value){
			Node<T1*> *newNode = new Node<T1*>;			// ノード新規追加
			newNode->value = (T1*)value;				// 値の代入

			// リンクの繋ぎ変え(addFirstとやることはほぼ同じ)
			newNode->prev = this->nullptrKUN->prev;		// 新規作成ノードの前ノードに番兵の前ノードを設定
			newNode->next = this->nullptrKUN;			// 新規作成ノードの次ノードに番兵を設定
			this->nullptrKUN->prev->next = newNode;		// 番兵の前ノードの次ノードを新規作成したノードに設定
			this->nullptrKUN->prev = newNode;			// 番兵の前ノードを新規作成したノードに設定
		}

		// valを持つ最初のノードを削除
		void deleteValue(const T1* value){
			deleteNode(listSearch(value));
		}

		// 先頭のノードを削除
		void deleteFirst(){
			deleteNode(nullptrKUN->next);
		}

		// 末尾のノードを削除
		void deleteLast(){
			deleteNode(nullptrKUN->prev);
		}

		// 末尾から指定数番目ノードの内のvalを書き換える(存在しないノードを指定した場合はfalseを返す)
		bool updateLast(const T1* val, const int nodeNum){
			Node<T1*> *current = this->nullptrKUN->prev;
			for(int i = 0; i < nodeNum; i++){
				if(current == this->nullptrKUN){
					return false;						// 存在しないノードを指定した場合はfalseを返す(何もしない)
				}
				current = current->prev;				// 後ろへ
			}
			current->value = (T1*)val;					// 上書き
			return true;
		}

		// 先頭から指定数番目ノードの内のvalを書き換える(存在しないノードを指定した場合はfalseを返す)
		bool updateFirst(const T1* val, const int nodeNum){
			Node<T1*> *current = this->nullptrKUN->next;
			for(int i = 0; i < nodeNum; i++){
				if(current == this->nullptrKUN){
					return false;						// 存在しないノードを指定した場合はfalseを返す(何もしない)
				}
				current = current->next;				// 前へ
			}
			current->value = (T1*)val;					// 上書き
			return true;
		}

		// 先頭ノードのvalを取得
		T1* getValueNodeFirst() const{
			return (T1*)this->nullptrKUN->next->value;
		}

		// 末尾ノードのvalを取得
		T1* getValueNodeLast() const{
			return this->nullptrKUN->prev->value;
		}

		// 末尾から指定数番目のvalを取得。存在しないノードを指定した場合nullptrを返す
		T1* getValueSelectNodeFirst(const int nodeNum) const{
			Node<T1*> *current = nullptrKUN->next;		// 次のノードを現在のノードとして扱う
			T1* val = nullptrKUN->value;				// 保存用
			val = current->value;						// 現ノードの値を代入
			// 指定番号のノードまで前から検索
			for(int cnt = 0; cnt < nodeNum; cnt++){
				current = current->next;				// 次のノードへ

				// 前回の値(ポインタ)と同じ場合はそれ以降は存在しないので探索終了
				// 存在しない場合は型最大までを返す
				if(nullptrKUN == current){
					return nullptr;
				}
				val = current->value;					// 現ノードの値を代入
			}
			return val;
		}

		// 末尾から指定数番目のvalを取得。存在しないノードを指定した場合nullptrを返す
		T1* getValueSelectNodeLast(const int nodeNum) const{
			Node<T1*> *current = nullptrKUN->prev;		// 次のノードを現在のノードとして扱う
			T1* val = nullptrKUN->value;				// 保存用
			val = current->value;						// 現ノードの値を代入
			// 指定番号のノードまで前から検索
			for(int cnt = 0; cnt < nodeNum; cnt++){
				current = current->prev;				// 前のノードへ

				// 前回の値(ポインタ)と同じ場合はそれ以降は存在しないので探索終了
				// 存在しない場合は型最大までを返す
				if(nullptrKUN == current){
					return nullptr;
				}
				val = current->value;					// 現ノードの値を代入
			}
			return val;
		}

	};

}


#endif /* __LINKEDLIST_H__ */
