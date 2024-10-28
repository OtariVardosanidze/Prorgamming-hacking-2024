# Как создавать новую ветку

1. Переключиться на `main`:
```
git checkout main
```
2. Обновить `main`:
```
git fetch origin main
git rebase origin/main
```
3. Создать новую ветку:
```
git checkout -b <Branch name>
```
В результате получается новая ветка, которая совпадает с main. В ней содержатся последнии изменения в main. 

Если вам нужно создать ветку от другой ветки, то вместо `main` переключаетесь на нее.

# Как разрешать конфликты при merge

1. Обновить `main`, подтянуть изменения с сервера:
```
git fetch origin main
```
2. Нужно заребейзить свою ветку (заменить базовый комит на то, что на нашей ветке):
```
git rebase origin/main
```
3. Если есть конфликты, то появятся файлы с конфликтами. Их нужно исправить вручную или каким-то merge tools.
4. Продолжить ребейз:
```
git rebase --continue
```
5. Если снова возникли конфликты, перейти к пункту 3.

# Создание pull-request

1. Закомитить свои изменения (локально сохранить):
```
git add <Your files>
git commit -m "Your commit message"
```
2. Запушить ваши изменения (перенести на сервер):
```
git push
```
Автоматически будет предложено, какую команду использовать. Например:
```
git push --set-upstream origin protobuf_inv
```
3. Далее вам будет предложено создать PR. Например:
```
Delta compression using up to 20 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (11/11), 962 bytes | 120.00 KiB/s, done.
Total 11 (delta 0), reused 11 (delta 0), pack-reused 0 (from 0)
remote:
remote: Create a pull request for 'protobuf_inv' on GitHub by visiting:
remote:      https://github.com/OtariVardosanidze/Prorgamming-hacking-2024/pull/new/protobuf_inv
remote:
To https://github.com/OtariVardosanidze/Prorgamming-hacking-2024.git
 * [new branch]      protobuf_inv -> protobuf_inv
branch 'protobuf_inv' set up to track 'origin/protobuf_inv'.
```
Можно просто перейти по предложенной ссылке. Далее уже создавать свой реквест.