#pragma once
class AkMml
{
	private:
		//--------------------------------------
		// ���s�I�v�V����
		//--------------------------------------
		AkMmlOption& opt;

		//--------------------------------------
		// ���s���G���[�R�[�h
		//--------------------------------------
		ErrorCode::ErrorCodeType errorcode;

		//--------------------------------------
		// �o�[�W�������̕\��
		//--------------------------------------
		inline void putVersion();

	public:
		AkMml(AkMmlOption&);
		~AkMml();
		void Run();
};

