#pragma once

#define DefineParser(f) virtual void f(std::vector<int32_t>)\
	{ throw "aho~"; }

namespace akmml
{
	class Converter
	{
		private:
			std::vector<uint8_t> seqdata[8];	// 8ch分データ領域を作成
			std::array<int8_t, 8> chs;		// 書き込み対象チャンネル

		public:
			// コンストラクタ
			Converter(){}
			// デストラクタ
			virtual ~Converter(){}
			// データ取得
			std::vector<uint8_t>* getSeqData(){ return this->seqdata; }

			//------------------------------------------------
			// コマンド変換関数
			//------------------------------------------------
	
			// オクターブ系
			DefineParser(OctaveSet)
			DefineParser(OctaveUp)
			DefineParser(OctaveDown)
			// 音色系
			DefineParser(Tone)
			// 音量系
			DefineParser(GVolume)
			DefineParser(Volume)
			DefineParser(Expression)
			DefineParser(Tremolo)
			// パン系
			DefineParser(Panpot)
			DefineParser(PanVibration)
			// ピッチ系
			DefineParser(Pitchbend)
			DefineParser(Moduration)
			DefineParser(Transpose)
			DefineParser(Detune)
			// 音色エンベロープ系
			DefineParser(AttackRate)
			DefineParser(DecayRate)
			DefineParser(SustainLevel)
			DefineParser(SustainRate)
			DefineParser(ResetEnv)
			// テンポ
			DefineParser(Tempo)
			// エコー系
			DefineParser(EchoVolume)
			DefineParser(Fir)
			DefineParser(Efb)
			// ノイズクロック
			DefineParser(NoiseClock)
			// スイッチ系
			DefineParser(DrumSet)
			DefineParser(EOn)
			DefineParser(PMOn)
			DefineParser(NOn)
			DefineParser(Portament)
			// ループ系
			DefineParser(LoopBegin)
			DefineParser(LoopBreak)
			DefineParser(LoopEnd)
	};
}
