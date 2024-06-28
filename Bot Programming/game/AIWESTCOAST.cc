#include "Player.hh"
#include <algorithm>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME WESTCOAST


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
    typedef vector<int> VI;
    typedef vector<pair<int,int>> VII;
    typedef vector<vector<bool>> VVB;
    typedef queue<pair<Pos,int>> QPI;
    typedef queue<pair<Pos,pair<int,int>>> QPII;

  int search_elevator(const Pos& p) {
    QPII q;
    VVB vis (rows(), vector<bool>(cols(), false));
    q.push({p, {-1,0}});
    vis[p.i][p.j] = true;
    if(cell(p).type == Elevator) return 9;

    int final_dir = -1;
    int min_dist = -1;
    while(not q.empty()) {
        Pos front = q.front().first;
        int direction = q.front().second.first;
        int dist = q.front().second.second;
        q.pop();
        if(((front.k == 1 and cell(front).id != -1 and unit(cell(front).id).player == me()) or cell(front).id == -1) and cell(front).type == Elevator) {
          if(final_dir == -1) {
            min_dist = dist;
            final_dir = direction;
          }
          else if(dist < min_dist) {
            final_dir = direction;
            min_dist = dist;
          }  
        }
        
        int k = 1;
        int maxk = k+7;
        if(dist > 3) maxk = k+3;
        while(k < maxk and dist <= 20) {
          Pos aux = front + Dir(k%8);
          if(pos_ok(aux) and not vis[aux.i][aux.j] and cell(aux).type != Rock and cell(aux).id == -1) {
            if(direction == -1) q.push({aux,{k%8,dist+1}});
            else q.push({aux, {direction,dist+1}});
            vis[aux.i][aux.j] = true;
          }
          ++k;
        }
    }
    if(final_dir != -1) return final_dir;
    else if(p.k == 0) return scan_cells(p);
    else return 10;
  }

  int scan_gems(const Pos& p, int& dist_gem) {
    QPII q;
    VVB vis (rows(), vector<bool>(cols(), false));
    q.push({p, {10,0}});
    vis[p.i][p.j] = true;
    int final_dir = -1;
    dist_gem = 0;
    while(not q.empty()) {
        Pos front = q.front().first;
        int direction = q.front().second.first;
        int dist = q.front().second.second;
        q.pop();
        if(cell(front).id == -1 and cell(front).gem) {
          if(final_dir == -1) {
            dist_gem = dist;
            final_dir = direction;
          }
          else if(dist < dist_gem) {
            final_dir = direction;
            dist_gem = dist;
          }
        }
        int k = random(0,7);
        int maxk = k+7;
        while(k < maxk and dist < 7) {
          Pos aux = front + Dir(k%8);
          if(pos_ok(aux) and not vis[aux.i][aux.j] and cell(aux).type == Outside and cell(aux).id == -1) {
            if(direction == 10) q.push({aux,{k%8,dist+1}});
            else q.push({aux, {direction,dist+1}});
            vis[aux.i][aux.j] = true;
          }
          ++k;
        }
    }
    if (final_dir == -1) return search_elevator(p);
    else return final_dir;
  }

  int scan_attack(const Pos& p, int& distancia, bool& pioneer) {
    QPII q;
    VVB vis (rows(), vector<bool>(cols(), false));
    q.push({p, {-1,0}});
    vis[p.i][p.j] = true;
    while(not q.empty()) {
        Pos front = q.front().first;
        int direction = q.front().second.first;
        int dist = q.front().second.second;
        q.pop();
        if(cell(front).id != -1 and unit(cell(front).id).player != me()) {
          distancia = dist; 
          if(unit(cell(front).id).type == Furyan and unit(cell(p).id).health >= unit(cell(front).id).health) {
            pioneer = false;
            return direction;
          }
          else if(unit(cell(front).id).type == Pioneer) {
            pioneer = true;
            return direction;
          }
        }
        int k = random(0,7);
        int maxk = k+7;
        while(k < maxk) {
          Pos aux = front + Dir(k%8);
          if(pos_ok(aux) and not vis[aux.i][aux.j] and cell(aux).type != Rock) {
            if(direction == -1) q.push({aux,{k%8, dist+1}});
            else q.push({aux, {direction, dist+1}});
            vis[aux.i][aux.j] = true;
          }
          ++k;
        }
    }
    return 10;
  }
  int scan_outside(const Pos& p) {
    Pos outside = p;
    outside.k = 1;
    int dist_danger = -1;
    int dir_danger = scan_danger(outside, false, dist_danger);
    int dist_gem = -1;
    int direct_gem = scan_gems(outside, dist_gem);
    if(dir_danger == -1 and dist_gem != 0 and dist_gem <= 7) return 8;
    if(dist_gem != 0 and dist_danger >= dist_gem/2 and direct_gem != dir_danger) return 8;
    else return scan_cells(p);
  }

  int scan_cells(const Pos& p) {
    QPI q;
    VVB vis (rows(), vector<bool>(cols(), false));
    q.push({p, -1});
    vis[p.i][p.j] = true;
    while(not q.empty()) {
        Pos front = q.front().first;
        int direction = q.front().second;
        q.pop();
        if(cell(front).type == Cave and cell(front).owner != me()) return direction;
        int k = random(0,7);
        int maxk = k+7;
        while(k < maxk) {
          Pos aux = front + Dir(k%8);
          if(pos_ok(aux) and not vis[aux.i][aux.j] and cell(aux).type == Cave and cell(aux).id == -1) {
            if(direction == -1) q.push({aux,k%8});
            else q.push({aux, direction});
            vis[aux.i][aux.j] = true;
          }
          ++k;
        }
    }
    return 10;
  }

  int scan_danger(const Pos& p, bool pioneer, int& dist_danger) {
    QPII q;
    VVB vis (rows(), vector<bool>(cols(), false));
    q.push({p, {-1,0}});
    vis[p.i][p.j] = true;
    while(not q.empty()) {
        Pos front = q.front().first;
        int direction = q.front().second.first;
        int dist = q.front().second.second;
        q.pop();
        if(cell(front).id != -1 and unit(cell(front).id).player != me()) {
          if(unit(cell(front).id).type == Hellhound) return direction;
          if(unit(cell(front).id).type == Necromonger) {
            dist_danger = dist;
            return direction;
          }
          if(unit(cell(front).id).type == Furyan and (pioneer or unit(cell(front).id).health > unit(cell(p).id).health)) return direction;

        }
        
        int k = random(0,7);
        int maxk = k+7;
        while(k < maxk and dist < 5) {
          Pos aux = front + Dir(k%8);
          if(pos_ok(aux) and not vis[aux.i][aux.j] and cell(aux).type != Rock) {
            if(direction == -1) q.push({aux,{k%8,dist+1}});
            else q.push({aux, {direction,dist+1}});
            vis[aux.i][aux.j] = true;
          }
          ++k;
        }
    }
    return -1;   //si no hi ha perill, es retorna -1
  }

  int escape_direction(const Pos& position, int direction) {
    direction = (direction+4)%8;  
    return escape(position, direction);
  }

  int escape(const Pos& p, int dir) {
    QPII q;
      VVB vis (rows(), vector<bool>(cols(), false));
      q.push({p, {-1,0}});
      vis[p.i][p.j] = true;
      int max_rad = 0;
      int final_dir = 10;
      while(not q.empty()) {
          Pos front = q.front().first;
          int direction = q.front().second.first;
          int dist = q.front().second.second;
          q.pop();
          if(dist >= 10) return direction;
          else if(dist > max_rad) {
            max_rad = dist;
            final_dir = direction;
          }
          
          int k = dir;
          int radius = 7;
          int sum = 0;
          int count = 0;
          if(dist < 5) count = 3;
          while(count < 8) {
            Pos aux = front + Dir(k%8);
            if(pos_ok(aux) and not vis[aux.i][aux.j] and cell(aux).type != Rock and cell(aux).id == -1) {
              if(direction == -1) q.push({aux,{k%8,dist+1}});
              else q.push({aux, {direction,dist+1}});
              vis[aux.i][aux.j] = true;
            }
            if(sum >= 0) sum = -(sum+1);
            else sum = -(sum-1);
            k += sum;
            ++count;
          }
      }
          return final_dir;
  }

  bool safe_zone(int j) {
    int ini = (round()*2 + 10)%80;
    int end = (round()*2 + 40)%80;
    if(ini < end) return (j > ini and j < end);
    else return j > ini or j < end;
  }

  VII priority_furyans(const VI& F) {
    int n = F.size();
    VII new_F(n);           
    for(int i = 0; i < n; ++i) {
      int id = F[i];
      new_F[i].first = id;
      Pos position = unit(id).pos;
      int dist_danger = 0;
      int dist_attack = 0;
      bool pioneer = true;
      scan_danger(position, false, dist_danger);
      scan_attack(position, dist_attack, pioneer);
      if(dist_attack == 1 and not pioneer) new_F[i].second = 0;
      else if(dist_danger >= 1 and dist_danger <= 5) new_F[i].second = 1;
      else if(dist_attack == 1 and pioneer) new_F[i].second = 2;
      else new_F[i].second = 5;
    }
    return new_F;
  }

  VII priority_pioneers(const VI& P, int& pion_ext) {
    int n = P.size(); 
    VII new_P(n); 
    int count = 0; 
    for(int i = 0; i < n; ++i) {
      int id = P[i];
      new_P[i].first = id;
      Pos position = unit(id).pos;
      int dist_danger = 0;

      if(unit(P[i]).pos.k == 1) ++count;

      scan_danger(position, true, dist_danger);
      if(dist_danger >= 1 and dist_danger <= 5) new_P[i].second = 3;
      else if(position.k == 1) new_P[i].second = 4;
      else new_P[i].second = 6;
    }
    pion_ext = count;
    return new_P;
  }

  void move_furyan(const int& id) {
    Pos position = unit(id).pos;
    int dist_danger = 0;
    int dist_attack = 0;
    bool pion = false;
    int danger = scan_danger(position, false, dist_danger);
    if(danger == -1) command(id, Dir(scan_attack(position, dist_attack, pion)));
    else command(id, Dir(escape_direction(position, danger)));
  }

  void move_pioneer(const int& id, const int& pion_ext) {
    int max_ext = 4;
    int dist_danger = 0;
    int dist_gem = 0;
    Pos position = unit(id).pos;
    
    int danger = scan_danger(position, true, dist_danger);
    if(danger != -1 and position.k == 0) command(id, Dir(escape_direction(position, danger)));
    else if(position.k == 1) command(id, Dir(scan_gems(position, dist_gem)));
    else if(pion_ext <= max_ext and safe_zone(position.j) and unit(id).health >= 30) {
      if(cell(position).type == Elevator and position.k == 0) command(id, Dir(scan_outside(position)));
      else command(id, Dir(search_elevator(position)));
    }
    else if (position.k == 0) command(id, Dir(scan_cells(position)));
    else command(id, Dir(9));
  }

void merge(VII& v, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    VII L(n1);
    VII R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = v[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = v[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 and j < n2) {
        if (L[i].second <= R[j].second) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(VII& v, int left, int right) {
    if (left < right) {
        int middle = (left + right)/ 2;

        mergeSort(v, left, middle);
        mergeSort(v, middle + 1, right);

        merge(v, left, middle, right);
    }
}

  //Si = 0, furyan está atacant a un furyan a una distancia de 1.
  //Si = 1, furyan está escapant d'un enemic a una distancia d'entre 1 o 5
  //Si = 2, furyan está atacant a un pioneer a una distancia de 1.
  //Si = 3, pioneer está escapant d'un enemic a una distancia d'entre 1 o 5
  //Si = 4, pioneer está a l'exterior
  //Si = 5, furyan está atacant a una distancia > 1
  //Si = 6, pioneer está capturant cell
VII order(int& pion_ext) {
  VI F = furyans(me());
  VI P = pioneers(me());
  int n = F.size();
  int m = P.size();
  VII new_F = priority_furyans(F);
  VII new_P = priority_pioneers(P, pion_ext);
  VII troops(n+m);
  for(int i = 0; i < n; ++i) troops[i] = new_F[i];
  for(int i = 0; i < m; ++i) troops[n+i] = new_P[i];
  //sort(troops.begin(), troops.end(), comp);
  mergeSort(troops, 0, n+m-1);
  return troops;
}

void move() {
  int pion_ext = 0;
  VII troops = order(pion_ext); 
  int n = troops.size();
  for(int i = 0; i < n; ++i) {
    int id = troops[i].first;
    if(unit(id).type == Furyan) move_furyan(id);
    else move_pioneer(id, pion_ext);
  }
}

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
