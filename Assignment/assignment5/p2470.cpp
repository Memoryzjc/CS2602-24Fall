#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    int T, D, P;
    cin >> T >> D >> P;

    // 存储每一天各帖子的浏览量
    vector<vector<int>> views(D, vector<int>(P));

    for (int i = 0; i < D; i++) {
        for (int j = 0; j < P; j++) {
            cin >> views[i][j];
        }
    }

    // 用于存储每天的热门帖子ID
    vector<int> result;

    // 维护一个 deque 用来存储每个帖子的浏览量的索引，确保其在最近 T 天内为递减顺序
    vector<deque<int>> windows(P);  // 每个帖子一个 deque，用来存储最近 T 天的浏览量的索引

    // 遍历每一天
    for (int day = 0; day < D; day++) {
        int best_post = -1;
        int best_views = -1;

        // 遍历每个帖子
        for (int post_id = 0; post_id < P; post_id++) {
            // 移除超出窗口的元素（即 T 天前的元素）
            while (!windows[post_id].empty() && windows[post_id].front() <= day - T) {
                windows[post_id].pop_front();
            }

            // 将当前天数的浏览量索引加入队列
            while (!windows[post_id].empty() && views[windows[post_id].back()][post_id] <= views[day][post_id]) {
                windows[post_id].pop_back();
            }

            // 加入当前的浏览量索引
            windows[post_id].push_back(day);

            // 获取当前帖子的最大浏览量（即窗口中的第一个元素）
            int max_views = views[windows[post_id].front()][post_id];

            // 更新当前热门帖
            if (max_views > best_views || (max_views == best_views && post_id > best_post)) {
                best_views = max_views;
                best_post = post_id;
            }
        }

        // 记录当前最热门的帖子ID（1-based index）
        result.push_back(best_post + 1);
    }

    // 输出结果
    for (int i = 0; i < D; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
