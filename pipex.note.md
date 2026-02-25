# bash
## commands
**soft linking**
- to create link: `ln -s path/to/target/ link_name`
- to remove link: `rm link_name`
- to overwrite existing link: `ln -sf /path/to/new_target existing_link_name`
- to check where a link points to: `ls -l link_name` will produce something like: `link_name -> /path/to/target`

# git
## commands
**create remote repo from cli for gitlab.com**
```bash
git init
git add .
git commit -m "Initial commit"
git branch -M main
git remote add origin git@gitlab.com:USERNAME/REPO_NAME.git
//git remote add origin https://gitlab.com/USERNAME/REPO_NAME.git // for https access
git push -u origin main
```
- `origin` & `main` being arbitrary default names.

# workflow
- link your current working project folders into your `~` for easier access.
