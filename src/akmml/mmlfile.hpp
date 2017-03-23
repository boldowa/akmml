#pragma once
namespace akmml
{
	class MmlFile : public File
	{
		private:
			// �Ȗ�
			std::string title;

			// �Q�[����
			std::string game;

			// ��Ȏ�
			std::string composer;

			// �쐬��
			std::string author;

			// �R�����g
			std::string comment;

			// �Ȃ̒���
			int playingTime;

			// �t�F�[�h����
			int fadeTime;

			// EDL�ő�l
			int maxEDL;

			// mml�ǂݍ��݃o�b�t�@
			std::string buffer;
			uint32_t buffInx;
			uint32_t mmlReadTimes;

			// �t�@�C���������ǂ���
			bool iseof;

			// ���s�����������ǂ���
			bool isnewline;

			// �s
			uint32_t line;

			// ��
			uint32_t column;

			// �s���ōŏ��̃X�y�[�X�ȊO�̕����̈ʒu
			uint32_t firstCharColumn;

			// TODO: �}�N��(���� - (��`�ۑ�) /�X�^�b�N - (���s))


		public:
			MmlFile(std::string);
			MmlFile(MmlFile&);
			~MmlFile();
			bool open(std::ios::openmode);

			//--------------------------------------
			// �֐�
			//--------------------------------------

			char getch();
			char getforward();
			char getusp();
			bool cmpstr(std::string);
			bool isFirstChar();
			void skipchars();
			void skipspaces();
	};
}
