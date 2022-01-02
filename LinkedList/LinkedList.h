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
			T1 value;		// �i�[����Ă���l
			Node *prev;		// �O�̃m�[�h
			Node *next;		// ���̃m�[�h
		};

		Node<T1> *nullptrKUN;		// �ʂ�یN(�ԕ�)NullPointer�ł͂Ȃ�

		// val�����ŏ��̃m�[�h�̃|�C���^��Ԃ�
		Node<T1> *listSearch(const T1 value){
			Node<T1> *current = nullptrKUN->next;	// ���̃m�[�h�����݂̃m�[�h�Ƃ��Ĉ���
			// ���̃m�[�h�����݂Ɠ����A�h���X�̏ꍇ�͂���ȍ~���݂��Ȃ��̂Ń��[�v�I��
			// �����̒l���o������܂őO���珇�Ɍ������Ă���
			while(current != nullptrKUN && current->value != value){
				current = current->next;			// ���̃m�[�h��
			}
			return current;
		};

		// �����ɗ^����ꂽ�m�[�h���폜
		void deleteNode(Node<T1> *node){
			if(node == nullptrKUN){
				return;  // node���ԕ��̎��͉������Ȃ�
			}
			// �����N�Ȃ��ς�
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;  // ���������
		};

	public:
		// constructor
		LinkedList(){
			this->nullptrKUN = new Node<T1>;
			this->nullptrKUN->next = this->nullptrKUN;		// �ԕ��̃m�[�h�A�h���X����
			this->nullptrKUN->prev = this->nullptrKUN;		// �ԕ��̃m�[�h�A�h���X����
			this->nullptrKUN->value = 0;					// �����l�Ƃ���0����
		};

		// �擪�ɒǉ�
		void addFirst(const T1 value){
			Node<T1> *newNode = new Node<T1>;			// �m�[�h�̐V�K�쐬
			newNode->value = value;						// �V�K�쐬�����m�[�h�ɒl�̑��

			// �����N�̂Ȃ��ւ�(�m�[�h0�ƃm�[�h1�̊Ԃɋ��݂��ފ���.�m�[�h0��nullprtKUN)
			newNode->next = this->nullptrKUN->next;		// �V�K�쐬�����m�[�h�̎��m�[�h��Ƃ��Č��݂̃m�[�h�̎��m�[�h�A�h���X����
			newNode->prev = this->nullptrKUN;			// �V�K�쐬�����m�[�h�̑O�m�[�h��Ƃ��Č��݂�s�m�[�h�A�h���X����
			this->nullptrKUN->next->prev = newNode;		// ���݂̃m�[�h�̎��m�[�h�̑O�m�[�h�Ƃ��ĂɐV�K�쐬�����m�[�h�A�h���X����
			this->nullptrKUN->next = newNode;			// ���݂̃m�[�h�̎��m�[�h�Ƃ��ĐV�K�쐬�����m�[�h�A�h���X����
		};

		// �����ɒǉ�
		void addLast(const T1 value){
			Node<T1> *newNode = new Node<T1>;			// �m�[�h�V�K�ǉ�
			newNode->value = value;						// �l�̑��

			// �����N�̌q���ς�(addFirst�Ƃ�邱�Ƃ͂قړ���)
			newNode->prev = this->nullptrKUN->prev;		// �V�K�쐬�m�[�h�̑O�m�[�h�ɔԕ��̑O�m�[�h��ݒ�
			newNode->next = this->nullptrKUN;			// �V�K�쐬�m�[�h�̎��m�[�h�ɔԕ���ݒ�
			this->nullptrKUN->prev->next = newNode;		// �ԕ��̑O�m�[�h�̎��m�[�h��V�K�쐬�����m�[�h�ɐݒ�
			this->nullptrKUN->prev = newNode;			// �ԕ��̑O�m�[�h��V�K�쐬�����m�[�h�ɐݒ�
		};

		// val�����ŏ��̃m�[�h���폜
		void deleteValue(const T1 value){
			deleteNode(listSearch(value));
		};

		// �擪�̃m�[�h���폜
		void deleteFirst(){
			deleteNode(nullptrKUN->next);
		};

		// �����̃m�[�h���폜
		void deleteLast(){
			deleteNode(nullptrKUN->prev);
		};

		// ��������w�萔�Ԗڃm�[�h�̓���val������������(���݂��Ȃ��m�[�h���w�肵���ꍇ��false��Ԃ�)
		bool updateLast(const T1 val, const int nodeNum){
			Node<T1> *current = this->nullptrKUN->prev;
			for(int i = 0; i < nodeNum; i++){
				if(current == this->nullptrKUN){
					return false;					// ���݂��Ȃ��m�[�h���w�肵���ꍇ��false��Ԃ�(�������Ȃ�)
				}
				current = current->prev;			// ����
			}
			current->value = val;					// �㏑��
			return true;
		};

		// �擪����w�萔�Ԗڃm�[�h�̓���val������������(���݂��Ȃ��m�[�h���w�肵���ꍇ��false��Ԃ�)
		bool updateFirst(const T1 val, const int nodeNum){
			Node<T1> *current = this->nullptrKUN->next;
			for(int i = 0; i < nodeNum; i++){
				if(current == this->nullptrKUN){
					return false;					// ���݂��Ȃ��m�[�h���w�肵���ꍇ��false��Ԃ�(�������Ȃ�)
				}
				current = current->next;			// �O��
			}
			current->value = val;					// �㏑��
			return true;
		};

		// �擪�m�[�h��val���擾
		T1 getValueNodeFirst() const{
			return this->nullptrKUN->next->value;
		};

		// �����m�[�h��val���擾
		T1 getValueNodeLast() const{
			return this->nullptrKUN->prev->value;
		};

		// �擪����w�萔�Ԗڂ�val���擾�B���݂��Ȃ��m�[�h���w�肵���ꍇ,�^�ő�܂�1�Ŗ��߂��l��Ԃ�
		T1 getValueSelectNodeFirst(const int nodeNum) const{
			Node *current = nullptrKUN->next;		// ���̃m�[�h�����݂̃m�[�h�Ƃ��Ĉ���
			T1 val = nullptrKUN->value;				// �ۑ��p
			val = current->value;					// ���m�[�h�̒l����
			// �w��ԍ��̃m�[�h�܂őO���猟��
			for(int cnt = 0; cnt < nodeNum; cnt++){
				current = current->next;			// ���̃m�[�h��

				// �O��̒l(�|�C���^)�Ɠ����ꍇ�͂���ȍ~�͑��݂��Ȃ��̂ŒT���I��
				// ���݂��Ȃ��ꍇ��0��Ԃ�
				if(nullptrKUN == current){
					return  0;
				}
				val = current->value;				// ���m�[�h�̒l����
			}
			return val;
		};

		// ��������w�萔�Ԗڂ�val���擾�B���݂��Ȃ��m�[�h���w�肵���ꍇ,�^�ő�܂�1�Ŗ��߂��l��Ԃ�
		T1 getValueSelectNodeLast(const int nodeNum) const{
			Node<T1> *current = nullptrKUN->prev;	// ���̃m�[�h�����݂̃m�[�h�Ƃ��Ĉ���
			T1 val = nullptrKUN->value;				// �ۑ��p
			val = current->value;					// ���m�[�h�̒l����
			// �w��ԍ��̃m�[�h�܂őO���猟��
			for(int cnt = 0; cnt < nodeNum; cnt++){
				current = current->prev;			// �O�̃m�[�h��

				// �O��̒l(�|�C���^)�Ɠ����ꍇ�͂���ȍ~�͑��݂��Ȃ��̂ŒT���I��
				// ���݂��Ȃ��ꍇ��0��Ԃ�
				if(nullptrKUN == current){
					return 0;
				}
				val = current->value;				// ���m�[�h�̒l����
			}
			return val;
		};

	};


	/* ======== T1���|�C���^�^�̏ꍇ ======== */

	// �������ꉻ
	template<class T1>
	class LinkedList<T1*>{
	private:
		template<class T1>
		class Node{
		public:
			T1 value;		// �i�[����Ă���l
			Node *prev;		// �O�̃m�[�h
			Node *next;		// ���̃m�[�h
		};

		Node<T1*> *nullptrKUN;		// �ʂ�یN(�ԕ�)NullPointer�ł͂Ȃ�

		// val�����ŏ��̃m�[�h�̃|�C���^��Ԃ�
		Node<T1*> *listSearch(const T1* value){
			Node<T1*> *current = nullptrKUN->next;	// ���̃m�[�h�����݂̃m�[�h�Ƃ��Ĉ���
			// ���̃m�[�h�����݂Ɠ����A�h���X�̏ꍇ�͂���ȍ~���݂��Ȃ��̂Ń��[�v�I��
			// �����̒l���o������܂őO���珇�Ɍ������Ă���
			while(current != nullptrKUN && current->value != value){
				current = current->next;			// ���̃m�[�h��
			}
			return current;
		}

		// �����ɗ^����ꂽ�m�[�h���폜
		void deleteNode(Node<T1*> *node){
			if(node == nullptrKUN){
				return;		// node���ԕ��̎��͉������Ȃ�
			}
			// �����N�Ȃ��ς�
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;	// ���������
		}

	public:
		// constructor
		LinkedList(){
			this->nullptrKUN = new Node<T1*>;
			this->nullptrKUN->next = this->nullptrKUN;		// �ԕ��̃m�[�h�A�h���X����
			this->nullptrKUN->prev = this->nullptrKUN;		// �ԕ��̃m�[�h�A�h���X����
			this->nullptrKUN->value = nullptr;				// �����l�Ƃ���nullprt����
		}

		// �擪�ɒǉ�
		void addFirst(const T1 *value){
			Node<T1*> *newNode = new Node<T1*>;			// �m�[�h�̐V�K�쐬
			newNode->value = (T1*)value;				// �V�K�쐬�����m�[�h�ɒl�̑��

			// �����N�̂Ȃ��ւ�(�m�[�h0�ƃm�[�h1�̊Ԃɋ��݂��ފ���.�m�[�h0��nullprtKUN)
			newNode->next = this->nullptrKUN->next;		// �V�K�쐬�����m�[�h�̎��m�[�h��Ƃ��Č��݂̃m�[�h�̎��m�[�h�A�h���X����
			newNode->prev = this->nullptrKUN;			// �V�K�쐬�����m�[�h�̑O�m�[�h��Ƃ��Č��݂�s�m�[�h�A�h���X����
			this->nullptrKUN->next->prev = newNode;		// ���݂̃m�[�h�̎��m�[�h�̑O�m�[�h�Ƃ��ĂɐV�K�쐬�����m�[�h�A�h���X����
			this->nullptrKUN->next = newNode;			// ���݂̃m�[�h�̎��m�[�h�Ƃ��ĐV�K�쐬�����m�[�h�A�h���X����
		}

		// �����ɒǉ�
		void addLast(const T1 *value){
			Node<T1*> *newNode = new Node<T1*>;			// �m�[�h�V�K�ǉ�
			newNode->value = (T1*)value;				// �l�̑��

			// �����N�̌q���ς�(addFirst�Ƃ�邱�Ƃ͂قړ���)
			newNode->prev = this->nullptrKUN->prev;		// �V�K�쐬�m�[�h�̑O�m�[�h�ɔԕ��̑O�m�[�h��ݒ�
			newNode->next = this->nullptrKUN;			// �V�K�쐬�m�[�h�̎��m�[�h�ɔԕ���ݒ�
			this->nullptrKUN->prev->next = newNode;		// �ԕ��̑O�m�[�h�̎��m�[�h��V�K�쐬�����m�[�h�ɐݒ�
			this->nullptrKUN->prev = newNode;			// �ԕ��̑O�m�[�h��V�K�쐬�����m�[�h�ɐݒ�
		}

		// val�����ŏ��̃m�[�h���폜
		void deleteValue(const T1* value){
			deleteNode(listSearch(value));
		}

		// �擪�̃m�[�h���폜
		void deleteFirst(){
			deleteNode(nullptrKUN->next);
		}

		// �����̃m�[�h���폜
		void deleteLast(){
			deleteNode(nullptrKUN->prev);
		}

		// ��������w�萔�Ԗڃm�[�h�̓���val������������(���݂��Ȃ��m�[�h���w�肵���ꍇ��false��Ԃ�)
		bool updateLast(const T1* val, const int nodeNum){
			Node<T1*> *current = this->nullptrKUN->prev;
			for(int i = 0; i < nodeNum; i++){
				if(current == this->nullptrKUN){
					return false;						// ���݂��Ȃ��m�[�h���w�肵���ꍇ��false��Ԃ�(�������Ȃ�)
				}
				current = current->prev;				// ����
			}
			current->value = (T1*)val;					// �㏑��
			return true;
		}

		// �擪����w�萔�Ԗڃm�[�h�̓���val������������(���݂��Ȃ��m�[�h���w�肵���ꍇ��false��Ԃ�)
		bool updateFirst(const T1* val, const int nodeNum){
			Node<T1*> *current = this->nullptrKUN->next;
			for(int i = 0; i < nodeNum; i++){
				if(current == this->nullptrKUN){
					return false;						// ���݂��Ȃ��m�[�h���w�肵���ꍇ��false��Ԃ�(�������Ȃ�)
				}
				current = current->next;				// �O��
			}
			current->value = (T1*)val;					// �㏑��
			return true;
		}

		// �擪�m�[�h��val���擾
		T1* getValueNodeFirst() const{
			return (T1*)this->nullptrKUN->next->value;
		}

		// �����m�[�h��val���擾
		T1* getValueNodeLast() const{
			return this->nullptrKUN->prev->value;
		}

		// ��������w�萔�Ԗڂ�val���擾�B���݂��Ȃ��m�[�h���w�肵���ꍇnullptr��Ԃ�
		T1* getValueSelectNodeFirst(const int nodeNum) const{
			Node<T1*> *current = nullptrKUN->next;		// ���̃m�[�h�����݂̃m�[�h�Ƃ��Ĉ���
			T1* val = nullptrKUN->value;				// �ۑ��p
			val = current->value;						// ���m�[�h�̒l����
			// �w��ԍ��̃m�[�h�܂őO���猟��
			for(int cnt = 0; cnt < nodeNum; cnt++){
				current = current->next;				// ���̃m�[�h��

				// �O��̒l(�|�C���^)�Ɠ����ꍇ�͂���ȍ~�͑��݂��Ȃ��̂ŒT���I��
				// ���݂��Ȃ��ꍇ�͌^�ő�܂ł�Ԃ�
				if(nullptrKUN == current){
					return nullptr;
				}
				val = current->value;					// ���m�[�h�̒l����
			}
			return val;
		}

		// ��������w�萔�Ԗڂ�val���擾�B���݂��Ȃ��m�[�h���w�肵���ꍇnullptr��Ԃ�
		T1* getValueSelectNodeLast(const int nodeNum) const{
			Node<T1*> *current = nullptrKUN->prev;		// ���̃m�[�h�����݂̃m�[�h�Ƃ��Ĉ���
			T1* val = nullptrKUN->value;				// �ۑ��p
			val = current->value;						// ���m�[�h�̒l����
			// �w��ԍ��̃m�[�h�܂őO���猟��
			for(int cnt = 0; cnt < nodeNum; cnt++){
				current = current->prev;				// �O�̃m�[�h��

				// �O��̒l(�|�C���^)�Ɠ����ꍇ�͂���ȍ~�͑��݂��Ȃ��̂ŒT���I��
				// ���݂��Ȃ��ꍇ�͌^�ő�܂ł�Ԃ�
				if(nullptrKUN == current){
					return nullptr;
				}
				val = current->value;					// ���m�[�h�̒l����
			}
			return val;
		}

	};

}


#endif /* __LINKEDLIST_H__ */
