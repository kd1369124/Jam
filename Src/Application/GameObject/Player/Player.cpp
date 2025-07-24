#include "Player.h"
#include"../../Scene/SceneManager.h"
#include"../../GameObject/Treasure/Treasure.h"
// 宝箱を1つ設置（テスト用）
TreasureBox treasureBox({ 0, 0, 30 });

void Player::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/a/a.gltf"); // プレイヤーモデル読み込み
	m_pCollider = std::make_unique<KdCollider>();
}

void Player::Update()
{
	Math::Vector3 dir = {};  // 移動方向
	bool moveFlg = false;    // 移動中フラグ

	// キー入力で移動方向を設定
	if (GetAsyncKeyState('W') & 0x8000)
	{
		dir += Math::Vector3(0, 0, 1); // 前進
		moveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		dir += Math::Vector3(0, 0, -1); // 後退
		moveFlg = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		dir += Math::Vector3(-1, 0, 0); // 左移動
		moveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		dir += Math::Vector3(1, 0, 0); // 右移動
		moveFlg = true;
	}

	if (moveFlg)
	{
		dir.Normalize();

		m_pos += dir * 0.2f; // プレイヤー移動

		// 向きを移動方向に合わせる
		m_angle = DirectX::XMConvertToDegrees(atan2(dir.x, dir.z));

		Math::Matrix rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
		Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);

		m_mWorld = rot * trans; // ワールド行列更新
	}

	KdCollider::SphereInfo sphereInfo;
	sphereInfo.m_sphere.Center = m_pos/* + Math::Vector3(0, 1.0f, 0)*/; // 球の中心をプレイヤーの少し上に
	sphereInfo.m_sphere.Radius = 40.0f;
	sphereInfo.m_type = KdCollider::TypeEvent; // ダメージ用コライダーとして設定


	// 判定結果を格納するリスト
	std::vector<std::pair<KdCollider::CollisionResult, std::shared_ptr<KdGameObject>>> collisionPairs;
	// ワールド上の全オブジェクトと衝突判定を行う
	for (const auto& obj : SceneManager::Instance().GetObjList())
	{
		std::list<KdCollider::CollisionResult> tempResults;
		obj->Intersects(sphereInfo, &tempResults);

		for (auto& ret : tempResults)
		{
			collisionPairs.emplace_back(ret, obj); // 衝突結果とオブジェクトをペアで保存}
		}
	}
	float minDistSq = std::numeric_limits<float>::max();
	std::shared_ptr<KdGameObject> closestHitObj = nullptr;
	Math::Vector3 closestOffset;

	for (auto& [ret, obj] : collisionPairs)
	{
		// 削除予定のオブジェクトはスキップ（仮に IsExpired 関数があるとする）
		if (obj->IsExpired()) continue;

		float distSq = (ret.m_hitPos - m_pos).LengthSquared();
		if (distSq < minDistSq)
		{
			minDistSq = distSq;
			closestHitObj = obj;
			closestOffset = ret.m_hitPos - m_pos;
		}
	}

	// プレイヤーと宝箱の距離を計算
	if (closestHitObj)
	{

		float distance = (closestHitObj->GetPos() - m_pos).Length();

		static float soundTimer = 0.0f; // 効果音タイマー
		const float deltaTime = 1.0f / 60.0f; // 仮想フレーム時間

		soundTimer += deltaTime;

		float interval = 0.0f; // 効果音の再生間隔

		// 距離に応じて効果音の間隔設定
		if (distance < 30.0f)      interval = 3.0f;   // 遠い
		if (distance < 15.0f)      interval = 1.5f;   // 中距離
		if (distance < 7.0f)       interval = 0.5f;   // 近距離

		// 宝箱が未開封なら距離に応じて効果音再生
		if (!treasureBox.isOpened && interval > 0.0f && soundTimer >= interval)
		{
			soundTimer = 0.0f; // タイマーリセット

			if (distance < 7.0f)
			{
				KdDebugGUI::Instance().AddLog("sound 3！Item Near\n");
			}
			else if (distance < 15.0f)
			{
				KdDebugGUI::Instance().AddLog("sound 2！Item Mid Range\n");
			}
			else if (distance < 30.0f)
			{
				KdDebugGUI::Instance().AddLog("sound 1！Item Far\n");
			}
		}

		static bool wasFPressed = false; // Fキー押しっぱなし判定

		// プレイヤーが宝箱の近くにいる場合
		if (distance < 7.0f)
		{
			if (!treasureBox.isOpened && (GetAsyncKeyState('F') & 0x8000))
			{
				if (!wasFPressed) // Fキー初押し検出
				{
					treasureBox.isOpened = true; // 宝箱開封
					KdDebugGUI::Instance().AddLog("You got a chest!\n");
					GetItemFromTreasure(); // アイテム取得処理
					closestHitObj->HitOn();
				}
				wasFPressed = true;
			}
			else
			{
				wasFPressed = false;
			}
		}

	}
}

void Player::DrawLit()
{
	// モデル描画
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}


void Player::GetItemFromTreasure()
{
	// アイテム取得ログ
	KdDebugGUI::Instance().AddLog("Item obtained!\n");
}