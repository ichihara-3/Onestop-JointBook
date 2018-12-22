= Git/CI等の設定(編集長作業)

この章では、編集長が執筆前にやっておくとよい、Gitの設定と、CIの設定について述べます。必ずしもこの方法でなくてはならないわけではありませんが、ワンストップ本ということで、一つの方法として承知ください。

== Gitリポジトリの設定
本書もそうですが、できるだけ他の人に声をかけ始める前に環境構築は済ませておきましょう。Blogなどで告知記事を書く、Slack等で相談スペースを作る、書いてくれそうな人に直接声をかける、それらも重要ですが、すぐに執筆にとりかかれるように、企画が決まったら、執筆環境構築は最優先でやりましょう。

=== リポジトリはPublicか？Privateか？
まず考える必要があるのは、公開リポジトリでいくのか、プライベートリポジトリでいくのかです。公開リポジトリで行う場合、当然ですが、原稿ファイルが全世界に公開されます。見る人が見れば、ダウンロードもできますし、pdfをローカルで作ることも可能です。したがって、勝手にダウンロードされたくない！という場合はプライベートリポジトリにしましょう。ただし、GitHubの場合は、プライベート可能なOrganizationを作るのは有料になります。月9ドル(本稿執筆辞典で。約1000円/月)。フリーランスや本業で課金している場合、あるいはほかのGitサービス(GitLab等)を使う場合はPrivateでもいいかもしれません。

一方で、Publicでやる場合にもいくつかメリットがあります。

 * 新規参入者(あるいは参加検討中の人)がさらっと見に来やすい
 どんな感じで進んでいるかがわかります。また、過去のコミット履歴やエラー履歴なども（見る気になれば）見れます。著者陣がこんなところについて相談している、などもわかるり、役立つこともあるかもしれません。
 * 告知にちょっと有利な場合がある 
 RTしてくれる人が、「実は本文もGitで公開してる！」と驚きをもって告知してくれることがある。
 * 売り上げ上の影響は小さいと思われる
 本文を無料公開しているということは、売り上げに悪影響を与えるという懸念もあります。しかし、個人的には売り上げ影響はほとんどないと思います。本の存在を知って、買った人でないとGitをわざわざ検索しませんし、タダ見して買わない人は、本を買わないでしょう。後述しますが、執筆中はCIを設定しておくのが良いですが、原稿完成後にはCIを止める、あるいはCIへのリンクを消す、などはやってもいいかもしれませんね。
 * 無料！
 GitHubなどへのお布施という側面は否定しませんが、毎月費用かかるのはやだなー、と思うくらいなら、当面は無料で始めて構わないのではないでしょうか。

本書をはじめ、OneStop本シリーズは、実は公開のリポジトリでやっています。リポジトリを見ることで得られるものもあるでしょう。本書においては、Githubの無料かつPublicリポジトリを使う前提で話を進めます。

=== GitのOrganizationを作る

プロジェクトが決まったら、まずOrganizationを作りましょう。先述のようにPublicなOrganizationであれば無料で使用できます。

自分ひとりのリポジトリでやってもいいのですが、

左上から、New Organizationを選択します。

//image[01_NewOrganization][Organizationの新規作成]

Organizationの名前と、メールアドレスを入力して、最上段のFreeを選択します。すでに使われている名前だと、エラーが出ます。

//image[02_SetupNewOrganization][Organization設定入力]

新しいOrganizationができたら、メンバーを招待しますが、アテがなければとりあえず次に進みます。アンケートもスキップしてよいです。答えてもよいですが。

//image[04_SkipInvitation][Invitationはとりあえずスキップ]

//image[03_NewOrganizationDone][Organizationができた]

自分がPeopleに入っています。新しい人を入れる場合は、Invite Someoneから追加できます。

=== リポジトリの初期設定をする

次は、本のリポジトリを作って、準備を進めます。

何はともあれ、新しいリポジトリを作ります。Create Repositoryをクリックします。名前を適当に入れれば、新しいリポジトリができます。ただし、この時点ではまだなにも入っていない、すっからかんのリポジトリです。

本の初期ファイルを作りましょう。一から作ってもよいですが、既存のファイルをフォークしてきた方が早い気ですから、それをしましょう。

正攻法は別の人にコラム入れてもらうとして、ローカルを経由して初期設定する方法について述べます。

まず、もとにするReviewのファイルを探してきます。



=== CIの設定をする

PDFは自動で、参加者全員が同じ環境で作ったpdfが確認できる方が良いですよね？Windowsで書いている人、Mac上で書いている人、WordやMarkdownなどで書いている人、いろいろいますが、今回は最終的にRe:viewにコンバートすることを一旦の前提とします。ローカル環境を作っている人ばかりではありませんし、ローカル環境はそれぞれの人で異なります。Dockerで、なんていう話もありますが、新しく環境構築するのはたいへんです。

そこでCIの出番になります。クラウドの仮想環境、とでも思っておけばよいでしょうか。

WerckerCIを前提に話を進めます。

にアクセスし、IDを作りましょう。GitIDでも連携IDを作れるので、それで十分でしょう。

次に、左上のAdd applicationをクリックします。Create new Applicationというページに遷移しますので、上段のプルダウンから自分のIDを選び、下はGitHubを選び、次に行きます。

検索窓にOrganizationを入力すると、候補になるリポジトリが表示されますから、今回の対象になるリポジトリ（今回はOnestop-JointBook:この本）を指定し、次に行きます。

SSHの設定は、Recommended for public projectsとあるので、上のSSHアクセスを選択します。

最終確認画面に来ましたが、ここで忘れないようにしたいのが、「Make my app public」のチェックです。これをチェックしておかないと、ほかの参加者（=執筆者）がCIで生成されたpdfを見れません。

これで、CIの設定が終わりました。トップ画面が出ましたよね？設定ファイルの中に、Wercker.ymlがあり、リポジトリが更新されるとアプリが走り、PDFが生成されます。

一度何かのファイルをPushするなり、更新するなりして、CIのてすとをしておきましょう。CIが走り始め、1分ほどでpdfが生成されるはずです。試行錯誤の段階ではその時間は多少ストレスになりますが、執筆者全員が同じ環境で出力されたpdfを随時確認できるというメリットは大きいです。ローカル環境設定などに煩わされることもないですしね。



